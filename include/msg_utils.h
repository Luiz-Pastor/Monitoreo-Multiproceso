#ifndef MSG_UTILS_H
# define MSG_UTILS_H

# include "config.h"

# include <mqueue.h>
# include <sys/stat.h>

typedef struct e_msg {
	long	target;
	long	result;
} t_msg;

int	msg_init(int op_mode);
int	msg_destroy(mqd_t queue, int delete);

int	msg_send(long target, long result, mqd_t queue);
int	msg_recieve(t_msg *msg, mqd_t queue);

#endif