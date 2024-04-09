#include "../../include/miner.h"

/**
 * @brief	Function to print a argument error message
 * 
 * @param	error Type of error (errors defined on `t_error` enum on `miner.h`)
 * @param	argv Arguments
 * 
 * @return	1 always
*/
static int	arguments_error(t_error error, char **argv)
{
	switch (error)
	{
		case ARG_COUNT:
			printf("Argument error!\n\tUsage: %s <ROUNDS> <LAG>\n", argv[0]);
			break ;

		case ARG_ROUND:
			printf("Incorrect number to search! (\"%s\")\n", argv[1]);
			break ;

		case ARG_LAG:
			printf("Incorrect time of cooldown! (\"%s\")\n", argv[2]);
			break ;
		
		default:
			break ;
	}
	return (1);
}

/**
 * @brief	Function to save the arguments
 * 
 * @param	argc Number of arguments
 * @param	argv Arguments
 * @param	args Pointer to the struct in which the data will be saved
 * 
 * @return	`NONE` on success; otherwise, the error key
*/
static t_error	save_arguments(int argc, char **argv, t_args *args)
{
	if (argc != 3)
		return ARG_COUNT;	

	args->rounds = atoll(argv[1]);
	if (args->rounds < MIN_ROUNDS)
		return ARG_ROUND;

	args->lag = atoll(argv[2]);
	if (args->lag < MIN_LAG)
		return ARG_LAG;

	return NONE;	
}

int main(int argc, char *argv[])
{
	int		status;
	mqd_t	queue;
	t_error	args_error;
	t_args arguments;


	/* Arguments save */
	args_error = save_arguments(argc, argv, &arguments);
	if (args_error)
		return (arguments_error(args_error, argv));

	/* Open the msg region */
	queue = msg_init(MINER);
	if (queue == -1)
	{
		perror("Queue creation");
		return (1);
	}

	/* Miner loop. If there is any problem, the error is printed inside */
	status = miner_routine(&arguments, queue);

	/* Freed the msg section */
	msg_destroy(queue, NO_DELETE);
	
	/* Exit with the search end status */
	return status;
}
