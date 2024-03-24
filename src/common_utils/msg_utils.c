# include "../../include/msg_utils.h"

int	msg_init()
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

int	msg_destroy(mqd_t queue, int delete)
{
	if (mq_close(queue))
		return 1;
	
	if (delete)
	{
		if (mq_unlink(MSG_QUEUE_NAME))
			return 1;
	}
	
	return (0);
}

int	msg_send(long target, long result, mqd_t queue)
{
	t_msg	msg;

	msg.target = target;
	msg.result = result;

	return mq_send(queue, (const char *)&msg, sizeof(t_msg), 0);
}