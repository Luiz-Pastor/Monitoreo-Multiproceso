#ifndef MSG_UTILS_H
# define MSG_UTILS_H

# include "config.h"

# include <mqueue.h>
# include <sys/stat.h>

typedef struct e_msg {
	long	target;
	long	result;
} t_msg;

/**
 * @brief	It open a msg queue, depending of the open mode
 * 
 * @param	op_mode Opening mode. Can be `MINER`, `MONITOR` or `CHECKER`
 * 
 * @return	The message queue file descriptor, or -1 in error case (like problem
 * 			opening it or bad `op_mode`)
*/
mqd_t	msg_init(int op_mode);

/**
 * @brief	It destroys and delete the queue memory. By default, it closes the queue
 * 
 * @param	queue Queue file descriptor
 * @param	delete Delete flag. If it is a number different of 0, it unlink the queue
 * 
 * @return	0 on success execution, 1 on other cases 
*/
int		msg_destroy(mqd_t queue, int delete);

/**
 * @brief	It send a message, formed by a target and a result (using the struct `t_msg`).
 * 
 * @param	target Target to send
 * @param	result Result to send
 * @param	queue Message queue file descriptor
 * 
 * @return	The return of use the function `mq_send` 
*/
int		msg_send(long target, long result, mqd_t queue);

/**
 * @brief	It recieve a message from a queue
 * 
 * @param	msg Pointer to a variable in which the message is going to be saved
 * @param	queue Message queue file descriptor
*/
int		msg_recieve(t_msg *msg, mqd_t queue);

#endif