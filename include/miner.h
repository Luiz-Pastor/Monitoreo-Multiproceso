#ifndef MINER_H
# define MINER_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef enum {
	ARG_COUNT = 0,
	ARG_ROUND,
	ARG_LAG
} t_error;

/* Argument error manage */
int	arguments_error(t_error error, char *data);

#endif