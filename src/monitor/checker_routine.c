#include "../../include/monitor.h"

/**
 * Function that executes the routine of the checker proccess
*/
void	checker_routine(t_data *data)
{
	int		fd, index, flag;
	pid_t	pid;

	/* Create the semaphores and save it in any place that the other process can use it */
	fd = shared_memory_init(NULL, SEM_SHARED_MEMORY_NAME, SEM_BLOCK_LENGTH);
	if (fd < 0)
	{
		perror("Error while creating/opening the sempaphore shared memory");
		return ;
	}

	data->sem_shared = shared_memory_map(fd, SEM_BLOCK_LENGTH, ALL);
	shared_memory_destroy(fd, SEM_SHARED_MEMORY_NAME, NO_DELETE);
	if (!data->sem_shared)
	{
		perror("Error mapping the shared memory");
		return ;
	}

	if ((sem_init(&data->sem_shared[SEM_EMPTY], 1, SHARED_MEMORY_BLOCKS) == -1) ||
		sem_init(&data->sem_shared[SEM_MUTEX], 1, 1) == -1 ||
		sem_init(&data->sem_shared[SEM_FILL], 1, 0))
	{
		perror("Error while inicialiting a semaphone");
		return ;
	}

	/* Open the msg queue */
	data->queue = msg_init(CHECKER);
	if (data->queue == (mqd_t) -1)
	{
		perror("Error opening the msg queue");
		return ;
	}

	/* Printed the start msg */
	pid = getpid();
	printf("[%d] Checking blocks...\n", pid);

	/* Productor */
	index = 0;
	flag = 1;
	while (flag) {
		/* The turn is taken */
		sem_wait(&data->sem_shared[SEM_EMPTY]);
		sem_wait(&data->sem_shared[SEM_MUTEX]);

		/* Recieve the msg on the queue and saved the msg on the shaed memory */
		msg_recieve(&data->info_shared[index], data->queue);
		if (data->info_shared[index].target == END_VALUE &&
			data->info_shared[index].result == END_VALUE)
			flag = 0;

		index = (index + 1) % SHARED_MEMORY_BLOCKS;

		/* We leave the shift */
		sem_post(&data->sem_shared[SEM_MUTEX]);
		sem_post(&data->sem_shared[SEM_FILL]);

		/* LAG */
		usleep(data->lag);
	}

	/* Print stop msg and free the queue and the semaphores */
	printf("[%d] Finishing\n", pid);
	msg_destroy(data->queue, DELETE);
}