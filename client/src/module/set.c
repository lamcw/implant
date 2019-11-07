#define _GNU_SOURCE

#include <status.h>
#include <comm.h>
#include <module/set.h>
#include <lib/ketopt.h>
#include <lib/dynstr.h>

#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

enum { opt_set_pid, opt_set_uid, opt_set_gid };

static const ko_longopt_t set_longopts[] = {
	{ "uid", ko_required_argument, opt_set_uid },
	{ "gid", ko_required_argument, opt_set_gid },
	{ NULL, 0, 0 }
};

static int _set_uid(pid_t pid, uid_t uid)
{
	char *msg = NULL;

	int ret = dynstrcat(&msg, "set ");
	if (ret)
		goto f;

	char *tmp;
	ret = asprintf(&tmp, "--uid %d ", uid);
	if (ret < 0)
		goto f;

	ret = dynstrcat(&msg, tmp);
	if (ret) {
		free(tmp);
		goto f;
	}

	ret = comm(msg, strlen(msg));
	free(msg);
	return ret;

f:
	error("Failed to allocate system resources.\n");
	return ret;
}

static int _set_gid(pid_t pid, gid_t gid)
{
	char *msg = NULL;

	int ret = dynstrcat(&msg, "set ");
	if (ret)
		goto f;

	char *tmp;
	ret = asprintf(&tmp, "--gid %d ", gid);
	if (ret < 0)
		goto f;

	ret = dynstrcat(&msg, tmp);
	if (ret) {
		free(tmp);
		goto f;
	}
	ret = comm(msg, strlen(msg));
	free(msg);
	return ret;

f:
	error("Failed to allocate system resources.\n");
	return ret;
}

int set_command_handler(int argc, char **argv)
{
	bool set_uid = false;
	bool set_gid = false;
	uid_t uid;
	gid_t gid;

	int c;
	ketopt_t o = KETOPT_INIT;
	while ((c = ketopt(&o, argc, argv, 1, "", set_longopts)) >= 0) {
		switch (c) {
		case opt_set_uid:
			if (o.arg) {
				/* There is no good way to perform error
				 * detection here. The function strtol would
				 * need to be truncated. */
				set_uid = true;
				uid = atoi(o.arg);
			}
			break;
		case opt_set_gid:
			if (o.arg) {
				/* There is no good way to perform error
				 * detection here. The function strtol would
				 * need to be truncated. */
				set_gid = true;
				gid = atoi(o.arg);
			}
			break;
		}
	}

	if (o.ind == argc) {
		error("pid is a required argument.\n");
		return -1;
	}

	pid_t pid = atoi(argv[o.ind]);

	if (!set_uid && !set_gid) {
		error("One of --uid or --gid is required.\n");
		return -1;
	}

	return set_uid ? _set_uid(pid, uid) : _set_gid(pid, gid);
}
