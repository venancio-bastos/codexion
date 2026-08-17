/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vebastos <vebastos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 15:56:46 by vebastos          #+#    #+#             */
/*   Updated: 2026/08/17 15:59:53 by vebastos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	check_sim_stop(t_coder *coder)
{
	int	stop;

	pthread_mutex_lock(&coder->data->state_mutex);
	stop = coder->data->sim_stop;
	pthread_mutex_unlock(&coder->data->state_mutex);
	return (stop);
}

int	wait_in_queue(t_coder *coder)
{
	pthread_mutex_lock(&coder->data->queue_mutex);
	enqueue_coder(coder->data, coder);
	pthread_mutex_unlock(&coder->data->queue_mutex);
	while (1)
	{
		if (check_sim_stop(coder))
			return (1);
		pthread_mutex_lock(&coder->data->queue_mutex);
		if (coder->data->queue_head == coder)
		{
			pthread_mutex_unlock(&coder->data->queue_mutex);
			break ;
		}
		pthread_mutex_unlock(&coder->data->queue_mutex);
		usleep(500);
	}
	return (0);
}
