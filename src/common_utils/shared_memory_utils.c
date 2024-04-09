# include "../../include/shared_memory_utils.h"

/**
 * It inits a shared memory block. Also, it decide what type of process we are in
*/
int	shared_memory_init(int *whoami, char *name, size_t length)
{
	int	fd;
	int	prev_errno;

	/* Tried to create the block */
	fd = shm_open(name, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
	if (fd != -1)
	{
		/* The process is the checker */
		if (whoami)
			*whoami = CHECKER;

		/* The block has been created, so the size has to be put */
		if (ftruncate(fd, length))
		{
			prev_errno = errno;
			shared_memory_destroy(fd, name, DELETE);
			errno = prev_errno;
			return -1;
		}

		return fd;
	}

	/* Check if there was a problem while opening */
	if (errno != EEXIST)
		return -1;

	/* The block was created and exists, so we have to create a connection */
	fd = shm_open(name, O_RDWR, S_IRUSR | S_IWUSR);
	if (whoami)
		*whoami = MONITOR;
	return fd;
}

/**
 * Function to deletes a shared memory block. It also can remove the file (unlink it)
*/
int	shared_memory_destroy(int fd, char *name, int delete)
{
	if (close(fd))
		return 1;

	if (delete == DELETE)
	{
		if (shm_unlink(name))
			return 1;
	}

	return 0;
}

/**
 * It map a block of memory, by it file descriptor
*/
void	*shared_memory_map(int fd, size_t length, int whoami)
{
	int	perm = (whoami == CHECKER ? PROT_WRITE : PROT_READ);

	switch (whoami)
	{
	case CHECKER:
		perm = PROT_WRITE;
		break;
	
	case MONITOR:
		perm = PROT_READ;
		break;

	default:
		perm = PROT_READ | PROT_WRITE;
		break;
	}

	return mmap(NULL, length, perm, MAP_SHARED, fd, 0);
}

/**
 * If delete a block of memory mapped previously
*/
int	shared_memory_munmap(void *start, size_t length)
{
	return munmap(start, length);
}