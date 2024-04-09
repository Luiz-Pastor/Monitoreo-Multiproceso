#ifndef CONFIG_H
# define CONFIG_H

/* ARGUMENTS */
# define MIN_LAG	0					/*!< Min lag time */
# define MIN_ROUNDS	1					/*!< Min number of rounds */

/* MINER */
# define MAX_THREADS	10				/*!< Number of threads used */
# define INIT_TARGET	0				/*!< Initial target of the search */
# define POW_LIMIT		9997697			/*!< Maximum number for the hash result. */

/* MONITOR */
# define SEM_SHARED_MEMORY_NAME	"/sem_memory"	/*!< Name of the shared memory of semaphore */

/* MSG QUEUE */
# define MSG_QUEUE_NAME	"/miner"		/*!< Name of the message queue */
# define MSG_LENGTH		7				/*!< Max number of msg on the queue*/

/* SHARED MEMORY */
# define SHARED_MEMORY_NAME		"/monitor"	/*!< Name of the shared memory block */
# define SHARED_MEMORY_BLOCKS	6			/*!< Max number of memory blocks on the shared memory */

/*______________________________________________*/

/* PROCESS IDS */
# define MINER		0
# define ALL		0
# define MONITOR	1
# define CHECKER	2

/* MSG and SHARED MEMORY macros */
# define DELETE		1
# define NO_DELETE	0
# define END_VALUE -1


#endif