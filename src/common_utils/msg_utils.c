# include "../../include/msg_utils.h"

/**
 * It open a msg queue, depending of the open mode
*/
mqd_t	msg_init(int op_mode)
{
	mqd_t			queue = -1;
	struct mq_attr	atr;

	/* Flags of the msg queue */
	atr.mq_flags = 0;
	atr.mq_curmsgs = 0;
	atr.mq_maxmsg = MSG_LENGTH;
	atr.mq_msgsize = sizeof(t_msg);

	if (op_mode == MINER)
		queue = mq_open(MSG_QUEUE_NAME, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR, &atr);
	else if (op_mode == MONITOR || op_mode == CHECKER)
		queue = mq_open(MSG_QUEUE_NAME, O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR, &atr);
	return queue;
}

/**
 * It destroys and delete the queue memory. By default, it closes the queue
*/
int	msg_destroy(mqd_t queue, int delete)
{
	if (mq_close(queue))
		return 1;
	
	if (delete == DELETE)
	{
		if (mq_unlink(MSG_QUEUE_NAME))
			return 1;
	}
	
	return (0);
}

/**
 * It send a message, formed by a target and a result (using the struct `t_msg`).
*/
int	msg_send(long target, long result, mqd_t queue)
{
	t_msg	msg;

	msg.target = target;
	msg.result = result;

	return mq_send(queue, (const char *)&msg, sizeof(t_msg), 0);
}

/**
 * It recieve a message from a queue
*/
int	msg_recieve(t_msg *msg, mqd_t queue)
{
	return mq_receive(queue, (char *)msg, sizeof(t_msg), 0);
}