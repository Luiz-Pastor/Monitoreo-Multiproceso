#include "../../include/monitor.h"

void	monitor_routine(t_data *data)
{
	int		fd, index, flag;
	t_msg	*msg;
	pid_t	pid;

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

	/* Print the start msg */
	pid = getpid();
	printf("[%d] Printing blocks...\n", pid);

	/* Consumer */
	index = 0;
	flag = 1;
	while (flag) {
		/* The turn is taken */
		sem_wait(&data->sem_shared[SEM_FILL]);
		sem_wait(&data->sem_shared[SEM_MUTEX]);

		msg = &data->info_shared[index];

		/* Loop to recieve the msg from the shared memory and check if the result is OKAY*/
		if (msg->target == END_VALUE &&
			msg->result == END_VALUE)
			flag = 0;
		else {
			/* Check the msg */
			if (pow_hash(msg->result) == msg->target)
				printf("Solution accepted: %08ld --> %08ld\n", msg->target, msg->result);
			else
				printf("Solution rejected: %08ld !-> %08ld\n", msg->target, msg->result);

			index = (index + 1) % SHARED_MEMORY_BLOCKS;
		}

		/* The turn is leaved */
		sem_post(&data->sem_shared[SEM_MUTEX]);
		sem_post(&data->sem_shared[SEM_EMPTY]);

		/* LAG */
		usleep(data->lag);
	}

	/* Print the end msg */
	printf("[%d] Finishing\n", pid);
}
