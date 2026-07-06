#ifndef CODEXION_H_
#define CODEXION_H_

#include <stdio.h>
#include <string.h>

int scheduler_type(char *str);
int is_numeric(char *str);
int check_args(int ac, char **av);

#endif