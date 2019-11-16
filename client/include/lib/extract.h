#ifndef EXTRACT_H
#define EXTRACT_H

#include <status.h>
#include <log.h>
#include <fcntl.h>
#include <sys/types.h>
#include <syscall.h>

#define WRITE_FLAGS O_CREAT | O_EXCL | O_WRONLY

/**
 * Extract an object in the binary to file
 * 
 * This function will return the number of bytes written, 
 * or -1 if there was an error and no bytes were written.
 *
 * @param write_path Output location of resulting file
 * @param start_addr Object start location 
 * @param bytes_to_write Object size
 */

static ssize_t extract(const char *write_path, void *start_addr,
		       size_t bytes_to_write)
{
	int fd = open(write_path, WRITE_FLAGS, S_IRWXU);
	if (fd < 0) {
		IMLOG_DEBUG("Failed to open %s", write_path);
		return fd;
	}

	ssize_t written = write(fd, start_addr, bytes_to_write);
	close(fd);

	return written;
}

#endif /* EXTRACT_H */