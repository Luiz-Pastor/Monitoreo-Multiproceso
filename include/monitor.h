#ifndef MONITOR_H
# define MONITOR_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>

# include "pow.h"

/* Sem libraries */
# include "semaphore.h"
# include <sys/stat.h>
# include <sys/wait.h>

/* Include the msg functions */
# include "msg_utils.h"

/* Include the shm utils */
# include "shared_memory_utils.h"

/* Add the env variables */
# include "config.h"

# define SEM_EMPTY	0
# define SEM_MUTEX	1
# define SEM_FILL	2

# define MSG_BLOCK_LENGTH (sizeof(t_msg) * SHARED_MEMORY_BLOCKS)
# define SEM_BLOCK_LENGTH (sizeof(sem_t) * 3)

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
	t_msg	*info_shared;

	/* Sem zone */
	sem_t	*sem_shared;

	/* Msg queue */
	mqd_t	queue;
} t_data;


/**
 * @brief	Function that executes the routine of the monitor proccess
 * 
 * @param	data Pointer to the struct with all the data
*/
void	monitor_routine(t_data *data);

/**
 * @brief	Function that executes the routine of the checker proccess
 * 
 * @param	data Pointer to the struct with all the data
*/
void	checker_routine(t_data *data);

#endif