#define _GNU_SOURCE

#include <status.h>
#include <comm.h>
#include <module/kill.h>

#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int kill(pid_t pid)
{
	char *msg;
	int ret = asprintf(&msg, "kill %d", pid);
	if (ret < 0)
		goto f;

	return comm(msg, strlen(msg));

f:
	error("Failed to allocate system resources.\n");
	return ret;
}

int kill_command_handler(int argc, char **argv)
{
	if (argc < 2) {
		error("pid is a required argument.\n");
		return -1;
	}

	return kill(atoi(argv[1]));
}
