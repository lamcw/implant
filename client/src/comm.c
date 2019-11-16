#include <comm.h>
#include <status.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>

int comm(const char *msg, size_t len)
{
	assert(msg != NULL);
	assert(len > 0);

	int fd = open(IMPLANT_DEVICE_PATH, O_WRONLY);
	if (fd < 0) {
		error("Failed to communicate with the implant.\n");
		return fd;
	}

	int ret = write(fd, msg, len);
	if (ret != len) {
		error("Communication with the implant was interrupted.\n");
		if (ret >= 0)
			ret = -1;
		return ret;
	}

	close(fd);
	return 0;
}
