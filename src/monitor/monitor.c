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
	(void)data;
	// data->shared[0].target = 23;
	// data->shared[0].result = 10;

	/* TODO: create the semaphores and save it in any place that the other process can use it */
	/* TODO: open the msg queue */
	/* TODO: loop to recieve the msgs and send save it on the shared memory */
	/* TODO: Free the queue and the semaphores */
	
}

void	monitor_routine(t_data *data)
{
	(void)data;
	// printf("{%ld - %ld}\n", data->shared[0].target, data->shared[0].result);

	/* TODO: get the semaphores */
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
	fd = shared_memory_init(&data.whoami);
	if (fd == -1)
	{
		perror("Error while creating/opening the shared memory");
		return 1;
	}

	data.shared = shared_memory_map(fd, data.whoami);
	if (data.shared == MAP_FAILED)
	{
		perror("Error mapping the shared memory");
		shared_memory_destroy(fd, DELETE);
		return (1);
	}

	/* Process identification */
	if (data.whoami == CHECKER)
	{
		shared_memory_destroy(fd, NO_DELETE);
		checker_routine(&data);
	}
	else
	{
		shared_memory_destroy(fd, DELETE);
		monitor_routine(&data);
	}

	/* Resource release */
	if (shared_memory_munmap(data.shared))
	{
		perror("Error deleting the memory map");
		return 1;
	}

	return 0;
}