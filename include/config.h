#ifndef CONFIG_H
# define CONFIG_H

# define MIN_LAG 10					/*!< Min lag time */

# define MIN_ROUNDS 1				/*!< Min number of rounds */

# define MAX_THREADS 10				/*!< Number of threads used */

# define INIT_TARGET 0				/*!< Initial target of the search */

# define POW_LIMIT 9997697			/*!< Maximum number for the hash result. */

# define MSG_QUEUE_NAME "/miner"	/*!< Name of the message queue */

# define MAX_MSG	6				/*!< Max number of msg on the queue*/

typedef struct e_msg {
	long	target;
	long	result;
} t_msg;

#endif