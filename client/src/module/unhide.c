#define _GNU_SOURCE

#include <status.h>
#include <comm.h>
#include <module/unhide.h>
#include <lib/ketopt.h>

#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

enum { opt_unhide_pid, opt_unhide_file };

static const ko_longopt_t unhide_longopts[] = {
	{ "pid", ko_required_argument, opt_unhide_pid },
	{ "file", ko_required_argument, opt_unhide_file },
	{ NULL, 0, 0 }
};

static int unhide_process(pid_t pid)
{
	char *msg;
	int ret = asprintf(&msg, "unhide --pid %d", pid);
	if (ret < 0)
		return ret;

	ret = comm(msg, strlen(msg));
	free(msg);

	return ret;
}

static int unhide_file(char *path)
{
	char *msg;
	int ret = asprintf(&msg, "unhide --file %s", path);
	if (ret < 0)
		return ret;

	ret = comm(msg, strlen(msg));
	free(msg);

	return ret;
}

int unhide_command_handler(int argc, char **argv)
{
	pid_t pid = -1;
	char *file = NULL;

	int c;
	ketopt_t o = KETOPT_INIT;
	while ((c = ketopt(&o, argc, argv, 1, "", unhide_longopts)) >= 0) {
		switch (c) {
		case opt_unhide_pid:
			if (o.arg) {
				/* There is no good way to perform error
				 * detection here. The function strtol would
				 * need to be truncated. */
				pid = atoi(o.arg);
			}
			break;
		case opt_unhide_file:
			if (o.arg) {
				/* The file argument should be a single string. */
				file = o.arg;
			}
			break;
		}
	}

	if (pid != -1 && file != NULL) {
		error("Command flags --pid and --file are mutually exclusive.\n");
		return -1;
	}

	if (pid != -1)
		return unhide_process(pid);

	if (file != NULL)
		return unhide_file(file);

	error("Failed to find argument.\n");
	return -1;
}
