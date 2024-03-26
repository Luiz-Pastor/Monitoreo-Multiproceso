# include "../../include/shared_memory_utils.h"
# include <stdio.h>

# define MAX_BLOCK_LENGTH (sizeof(t_msg) * SHARED_MEMORY_BLOCKS)

int	shared_memory_init(int *whoami)
{
	int	fd;
	int	prev_errno;

	/* Tried to create the block */
	fd = shm_open(SHARED_MEMORY_NAME, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
	if (fd != -1)
	{
		/* The process is the checker */
		if (whoami)
			*whoami = CHECKER;

		/* The block has been created, so the size has to be put */
		if (ftruncate(fd, MAX_BLOCK_LENGTH))
		{
			prev_errno = errno;
			shared_memory_destroy(fd, DELETE);
			errno = prev_errno;
			return -1;
		}

		return fd;
	}

	/* Check if there was a problem while opening */
	if (errno != EEXIST)
		return -1;

	/* The block was created and exists, so we have to create a connection */
	fd = shm_open(SHARED_MEMORY_NAME, O_RDONLY, S_IRUSR | S_IWUSR);
	if (whoami)
		*whoami = MONITOR;
	return fd;
}

int	shared_memory_destroy(int fd, int delete)
{
	if (close(fd))
		return 1;

	if (delete == DELETE)
	{
		if (shm_unlink(SHARED_MEMORY_NAME))
			return 1;
	}

	return 0;
}

void	*shared_memory_map(int fd, int whoami)
{
	int	perm = (whoami == CHECKER ? PROT_WRITE : PROT_READ);

	return mmap(NULL, MAX_BLOCK_LENGTH, perm, MAP_SHARED, fd, 0);
}

int	shared_memory_munmap(void *start)
{
	return munmap(start, MAX_BLOCK_LENGTH);
}