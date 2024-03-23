#include "../../include/miner.h"

static t_error	save_arguments(int argc, char **argv, t_args *args)
{
	if (argc != 3)
		return ARG_COUNT;	

	args->rounds = atoll(argv[1]);
	if (args->rounds < MIN_ROUNDS || args->rounds > POW_LIMIT)
		return ARG_ROUND;

	args->lag = atoll(argv[2]);
	if (args->lag < MIN_LAG)
		return ARG_LAG;

	return NONE;	
}

int main(int argc, char *argv[])
{
	int		status;
	t_error	args_error;
	t_args arguments;


	/* Arguments save */
	args_error = save_arguments(argc, argv, &arguments);
	if (args_error)
		return (arguments_error(args_error, argv));

	/* TODO: Open the msg region */

	/* Bucle de mineria */
	status = miner_routine(&arguments);

	/* TODO: Freed the msg section */
	
	return status;
}
