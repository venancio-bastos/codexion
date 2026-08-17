/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vebastos <vebastos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 13:56:15 by vebastos          #+#    #+#             */
/*   Updated: 2026/08/17 13:56:15 by vebastos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	handle_single_coder(t_coder *coder)
{
	pthread_mutex_lock(&coder->data->dongles[coder->left_dongle]);
	print_status(coder, "has taken a dongle");
	while (!check_sim_stop(coder))
		usleep(500);
	pthread_mutex_unlock(&coder->data->dongles[coder->left_dongle]);
}

static void	grab_dongles(t_coder *coder)
{
	pthread_mutex_lock(&coder->data->dongles[coder->left_dongle]);
	print_status(coder, "has taken a dongle");
	pthread_mutex_lock(&coder->data->dongles[coder->right_dongle]);
	print_status(coder, "has taken a dongle");
	pthread_mutex_lock(&coder->data->queue_mutex);
	coder->data->queue_head = coder->data->queue_head->next_in_queue;
	pthread_mutex_unlock(&coder->data->queue_mutex);
}

static void	compile_routine(t_coder *coder)
{
	if (coder->data->number_of_coders == 1)
	{
		handle_single_coder(coder);
		return ;
	}
	if (check_sim_stop(coder))
		return ;
	grab_dongles(coder);
	pthread_mutex_lock(&coder->data->state_mutex);
	coder->last_compile_start = get_current_time();
	pthread_mutex_unlock(&coder->data->state_mutex);
	print_status(coder, "is compiling");
	ft_usleep(coder->data->time_to_compile);
	pthread_mutex_lock(&coder->data->state_mutex);
	coder->compiles_count++;
	pthread_mutex_unlock(&coder->data->state_mutex);
	pthread_mutex_unlock(&coder->data->dongles[coder->left_dongle]);
	pthread_mutex_unlock(&coder->data->dongles[coder->right_dongle]);
}

void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	if (coder->id % 2 == 0)
		usleep(1000);
	while (!check_sim_stop(coder))
	{
		if (wait_in_queue(coder) == 1)
			break ;
		compile_routine(coder);
		print_status(coder, "is debugging");
		ft_usleep(coder->data->time_to_debug);
		print_status(coder, "is refactoring");
	}
	return (NULL);
}
