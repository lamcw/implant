#define _GNU_SOURCE

#include <status.h>
#include <comm.h>
#include <module/kill.h>
#include <lib/ketopt.h>

#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

enum { opt_kill_pid,
};

static const ko_longopt_t kill_longopts[] = { { "pid", ko_required_argument,
						opt_kill_pid },
					      { NULL, 0, 0 } };

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
	pid_t pid = -1;

	int c;
	ketopt_t o = KETOPT_INIT;
	while ((c = ketopt(&o, argc, argv, 1, "", kill_longopts)) >= 0) {
		switch (c) {
		case opt_kill_pid:
			if (o.arg) {
				/* There is no good way to perform error
				 * detection here. The function strtol would
				 * need to be truncated. */
				pid = atoi(o.arg);
			}
			break;
		}
	}

	if (pid == -1) {
		error("--pid is a required argument.\n");
		return -1;
	}

	return kill(pid);
}
