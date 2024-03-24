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

static int	init_msg()
{
	mqd_t			queue;
	struct mq_attr	atr;

	/* Flags of the msg queue */
	atr.mq_flags = 0;
	atr.mq_curmsgs = 0;
	atr.mq_maxmsg = MAX_MSG;
	atr.mq_msgsize = sizeof(t_msg);

	queue = mq_open(MSG_QUEUE_NAME, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR, &atr);
	return queue;
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
	queue = init_msg();
	if (queue == -1)
	{
		perror("Queue creation");
		return (1);
	}

	/* Miner loop */
	status = miner_routine(&arguments, queue);

	/* Freed the msg section */
	mq_close(queue);
	
	return status;
}
