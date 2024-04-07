#include "../../include/monitor.h"

t_error	save_arguments(int argc, char **argv, t_data *data)
{
	if (argc != 2)
		return ARG_COUNT;
	
	data->lag = atol(argv[1]);
	if (data->lag < MIN_LAG)
		return ARG_LAG;
	
	return NONE;
}

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

int main(int argc, char *argv[])
{
	int		fd;
	t_data	data;
	t_error	arg_error;

	if (argc != 2)
		printf("Error: %s\n", argv[0]);
	
	/* Argument checker */
	arg_error = save_arguments(argc, argv, &data);
	if (arg_error)
		return argument_error(arg_error, argv);

	/*
		Open the shared memory. Also set the argument the type of process (CHECKER or MONITOR).
		If the memory block is open correctly, it is mapped to the process.
	*/
	fd = shared_memory_init(&data.whoami, SHARED_MEMORY_NAME, MSG_BLOCK_LENGTH);
	if (fd == -1)
	{
		perror("Error while creating/opening the shared memory");
		return 1;
	}

	data.info_shared = shared_memory_map(fd, MSG_BLOCK_LENGTH, data.whoami);
	if (data.info_shared == MAP_FAILED)
	{
		perror("Error mapping the shared memory");
		shared_memory_destroy(fd, SHARED_MEMORY_NAME, DELETE);
		return (1);
	}

	/* Process identification */
	if (data.whoami == CHECKER)
	{
		shared_memory_destroy(fd, SHARED_MEMORY_NAME, NO_DELETE);
		checker_routine(&data);
	}
	else
	{
		shared_memory_destroy(fd, SHARED_MEMORY_NAME, DELETE);
		monitor_routine(&data);
	}

	/* Resource release */
	if (shared_memory_munmap(data.info_shared, MSG_BLOCK_LENGTH))
	{
		perror("Error deleting the memory map");
		return 1;
	}

	return 0;
}