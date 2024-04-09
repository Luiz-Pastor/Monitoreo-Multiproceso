#ifndef SHARED_MEMORY_UTILS_H
# define SHARED_MEMORY_UTILS_H

# include "msg_utils.h"
# include "config.h"

# include <sys/mman.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>

/**
 * @brief	It inits a shared memory block. Also, it decide what type of process we are in
 * 
 * @param	whoami Pointer to a variable that represents the type of process, that can
 * 			be `CHECKER` or `MONITOR`
 * @param	name The name that the shared memory will have
 * @param	length The length of the block
*/
int	shared_memory_init(int *whoami, char *name, size_t length);

/**
 * @brief	Function to deletes a shared memory block. It also can remove the file (unlink it)
 * 
 * @param	fd Shared memory file descriptor
 * @param	name Name of the shared memory block
 * @param	delete Flag to indicate to unlink the block
 * 
 * @return	0 in success, 1 on error case
*/
int	shared_memory_destroy(int fd, char *name, int delete);

/**
 * @brief	It map a block of memory, by it file descriptor
 * 
 * @param	fd The file descriptor of the block
 * @param	length The length of the block
 * @param	whoami The type of process. Depending of it, the section
 * 			will have different permissions
 * 
 * @return	The return value of `map` function, which is a pointer
 * 			to the start of the region, or `NULL` on error case
*/
void	*shared_memory_map(int fd, size_t length, int whoami);

/**
 * @brief	If delete a block of memory mapped previously
 * 
 * @param	start Pointer to the start of the mapped block
 * @param	length The length of the mapped block
 * 
 * @return	The return of the `munmap` function
*/
int		shared_memory_munmap(void *start, size_t length);

#endif