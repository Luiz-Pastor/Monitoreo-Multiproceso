#ifndef MSG_UTILS_H
# define MSG_UTILS_H

# include "config.h"

# include <mqueue.h>
# include <sys/stat.h>

# define DELETE		1
# define NO_DELETE	0

typedef struct e_msg {
	long	target;
	long	result;
} t_msg;

int	msg_init();
int	msg_destroy(mqd_t queue, int delete);

int	msg_send(long target, long result, mqd_t queue);

#endif