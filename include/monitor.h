#ifndef MONITOR_H
# define MONITOR_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>

/* Include the msg functions */
# include "msg_utils.h"

/* Include the shm utils */
# include "shared_memory_utils.h"

/* Add the env variables */
# include "config.h"

typedef enum {
	NONE = 0,
	ARG_COUNT,
	ARG_LAG
} t_error;

typedef struct s_data {

	/* Process id (MONITOR - CHECKER) */
	int		whoami;

	/* LAG, argv[1] */
	long	lag;

	/* Shared memory */
	t_msg	*shared;


} t_data;

/* Arguments checker */
int	argument_error(t_error error, char **argv);

#endif