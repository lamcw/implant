#include <util.h>
#include <log.h>

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

int erase(void)
{
	char *path = realpath("/proc/self/exe", NULL);
	if (path == NULL) {
		IMLOG_ERR("Failed to find the path to the running program");
		return -1;
	}

	int ret = remove(path);
	free(path);

	return ret;
}
