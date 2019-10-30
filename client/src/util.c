#include <util.h>
#include <debug.h>

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

int erase(void)
{
	char *path = realpath("/proc/self/exe", NULL);
	if (path == NULL) {
		IMLOG_DEBUG("Failed to find the path to the running program");
		return -1;
	}

	int ret = remove(path);
	free(path);

	return ret;
}
