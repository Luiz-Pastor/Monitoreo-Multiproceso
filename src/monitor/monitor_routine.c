#include "../../include/monitor.h"

void	monitor_routine(t_data *data)
{
	printf("Leer semaforos\n");
	int	fd;
	/* NOTE: leer todo el espacio para ver errores de valgrind */

	/* TODO: get the semaphores */
	fd = shared_memory_init(NULL, SEM_SHARED_MEMORY_NAME, SEM_BLOCK_LENGTH);
	if (fd < 0)
	{
		perror("Error while creating/opening the sempaphore shared memory");
		return ;
	}

	data->sem_shared = shared_memory_map(fd, SEM_BLOCK_LENGTH, ALL);
	shared_memory_destroy(fd, SEM_SHARED_MEMORY_NAME, DELETE);
	if (!data->sem_shared)
	{
		perror("Error mapping the shared memory");
		return ;
	}

	/* TODO: loop to recieve the msg from the shared memory and check if the result is OKAY*/
	/* TODO: free all the resources */
}