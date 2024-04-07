#include "../../include/monitor.h"

void	checker_routine(t_data *data)
{
	printf("Crear semaforo\n");

	int	fd;
	/* NOTE: fillear todo para ver problemas de valgrind */

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

	if ((sem_init(&data->sem_shared[SEM_EMPTY], 1, 0) == -1) ||
		sem_init(&data->sem_shared[SEM_MUTEX], 1, 0) == -1 ||
		sem_init(&data->sem_shared[SEM_FILL], 1, 0))
	{
		perror("Error while inicialiting a semaphone");
		return ;
	}

	/* TODO: open the msg queue */
	data->queue = msg_init(CHECKER);
	if (data->queue == (mqd_t) -1)
	{
		perror("Error opening the msg queue");
		return ;
	}

	/* TODO: loop to recieve the msgs and send save it on the shared memory */
	/* TODO: Free the queue and the semaphores */
	
}