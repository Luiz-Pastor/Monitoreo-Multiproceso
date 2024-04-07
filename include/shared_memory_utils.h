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

int	shared_memory_init(int *whoami, char *name, size_t length);
int	shared_memory_destroy(int fd, char *name, int delete);

void	*shared_memory_map(int fd, size_t length, int whoami);
int		shared_memory_munmap(void *start, size_t length);

#endif