#ifndef MINER_H
# define MINER_H

/* Generic libs */
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>

/* Threads lib */
# include <stdatomic.h>	/* Lib to use atomic variables*/
# include <pthread.h>

/* Msg libs */
# include "msg_utils.h"

/* Project macros */
# include "config.h"

/* Pow lib */
# include "pow.h"

typedef enum {
	NONE = 0,
	ARG_COUNT,
	ARG_ROUND,
	ARG_LAG
} t_error;

typedef struct s_args {
	long rounds;
	long lag;
} t_args;

typedef struct s_miner {

	pthread_t	thread;		/* Thread id */
	long		min;		/* Min number to search */
	long		max;		/* Max number to search */

	atomic_long		*f_active;	/* Flag that indicates if the thread must stop */
	atomic_long		*f_search;	/* Flag that indicates if the thread can search */
	atomic_long		*target;	/* Target to search  */
	atomic_long		*result;	/* Result of the search */
} t_miner;

/* Argument error manage */
int	arguments_error(t_error error, char **argv);

/* Function loop to found targets */
int	miner_routine(t_args *arguments, mqd_t queue);

#endif