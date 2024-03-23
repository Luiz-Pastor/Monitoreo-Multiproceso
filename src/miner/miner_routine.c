#include "../../include/miner.h"

void	*miner_search(void *arg) {
	long	i;
	t_miner	*miner;

	miner = (t_miner *) arg;

	/* Loop until the rounds are completed */
	while (atomic_load(miner->f_active))
	{
		/* If the search flag is up, the thread will serach the target */
		if (atomic_load(miner->f_search))
		{
			for (i = miner->min; i <= miner->max && atomic_load(miner->f_search); i++)
			{
				if (pow_hash(i) == atomic_load(miner->target))
				{
					atomic_store(miner->result, i);
					atomic_store(miner->f_search, 0);
					break ;
				}
			}
		}
	}
	return (NULL);
}

long	init_miners(t_miner *miners,
					atomic_long *f_active, atomic_long *f_search, atomic_long *target, atomic_long *result)
{
	long		i, threads_created;

	/* Init the common variables */
	(*f_active) = ATOMIC_VAR_INIT(1);
	(*f_search) = ATOMIC_VAR_INIT(0);
	(*target) = ATOMIC_VAR_INIT(0);
	(*result) = ATOMIC_VAR_INIT(-1);

	/* Init the miners struct */
	for (i = 0; i < MAX_THREADS; i++)
	{
		miners[i].f_active = &(*(f_active));
		miners[i].f_search = &(*(f_search));
		miners[i].target = &(*(target));
		miners[i].result = &(*(result));
	}

	/* Init the threads*/
	for (i = 0; i < MAX_THREADS; i++)
	{
		if (pthread_create(&miners[i].thread, NULL, miner_search, &miners[i]))
			break ;
	}
	threads_created = i;

	/* Depending of the miners created, the min and max field of each miner are setted */
	if (threads_created == 0)
		return (0);
	for (i = 0; i < threads_created; i++)
	{
		miners[i].min = (POW_LIMIT / threads_created) * i;
		miners[i].max = (POW_LIMIT / threads_created) * (i + 1) - 1;
	}
	miners[i - 1].max = POW_LIMIT;

	return threads_created;
}

int	miner_routine(t_args *arguments)
{
	long			i, threads_created;
	atomic_long		f_active, f_search, target, old_target, result;
	t_miner *miners;

	
	/* Creating the main array struct */
	miners = malloc(MAX_THREADS * sizeof(t_miner));
	if (!miners)
	{
		perror("malloc");
		return 1;
	}

	/* Init the miners with data */
	threads_created = init_miners(miners, &f_active, &f_search, &target, &result);
	if (threads_created == 0)
	{
		free(miners);
		perror("Threads");
		return  1;
	}

	/* Loop to search the number of the n rounds */
	old_target = ATOMIC_VAR_INIT(INIT_TARGET);
	for (i = 0; i < arguments->rounds; i++)
	{
		/* Setted the target and reseted the result variable */
		atomic_store(&target, atomic_load(&old_target));
		atomic_store(&result, -1);
		
		/* Changed the flags to start searching */
		atomic_store(&f_search, 1);
		while (atomic_load(&f_search));

		/* FIXME: Printed the result. The numbers must be sended by a msg */
		printf("Resultado: %07ld ----> %07ld\n", atomic_load(&target), atomic_load(&result));

		/* Saved the result for the next round and putted lag */
		atomic_store(&old_target, atomic_load(&result));
		if (i != arguments->rounds - 1)
			usleep(arguments->lag * 1000);
	}

	/* Collecting the threads and freed the memory used */
	atomic_store(&f_active, 0);
	for (i = 0; i < threads_created; i++)
		pthread_join(miners[i].thread, NULL);
	free(miners);

	return 0;
}