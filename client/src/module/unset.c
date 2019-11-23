#define _GNU_SOURCE

#include <status.h>
#include <comm.h>
#include <module/unset.h>
#include <lib/ketopt.h>
#include <lib/dynstr.h>

#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

enum { opt_unset_uid, opt_unset_gid };

static const ko_longopt_t unset_longopts[] = {
	{ "uid", ko_no_argument, opt_unset_uid },
	{ "gid", ko_no_argument, opt_unset_gid },
	{ NULL, 0, 0 }
};

static int unset(pid_t pid, bool unset_uid, bool unset_gid)
{
	char *msg = NULL;

	int ret = dynstrcat(&msg, "unset ");
	if (ret)
		goto f;

	char *tmp;
	ret = asprintf(&tmp, "%d ", pid);
	if (ret < 0)
		goto f;

	ret = dynstrcat(&msg, tmp);
	if (ret) {
		free(tmp);
		free(msg);
		goto f;
	}

	if (unset_uid) {
		ret = dynstrcat(&msg, "--uid ");
		if (ret) {
			free(tmp);
			free(msg);
			goto f;
		}
	}

	if (unset_gid) {
		ret = dynstrcat(&msg, "--gid");
		if (ret) {
			free(tmp);
			free(msg);
			goto f;
		}
	}

	ret = comm(msg, strlen(msg));
	free(tmp);
	free(msg);
	return ret;

f:
	error("Failed to allocate system resources.\n");
	return ret;
}

int unset_command_handler(int argc, char **argv)
{
	bool unset_uid = false;
	bool unset_gid = false;

	int c;
	ketopt_t o = KETOPT_INIT;
	while ((c = ketopt(&o, argc, argv, 1, "", unset_longopts)) >= 0) {
		switch (c) {
		case opt_unset_uid:
			unset_uid = true;
			break;
		case opt_unset_gid:
			unset_gid = true;
			break;
		}
	}

	if (o.ind == argc) {
		error("pid is a required argument.\n");
		return -1;
	}

	pid_t pid = atoi(argv[o.ind]);
	if (pid == 0) {
		error("pid not parsed.\n");
		return -1;
	}

	if (!unset_uid && !unset_gid) {
		error("One of --uid or --gid is required.\n");
		return -1;
	}

	return unset(pid, unset_uid, unset_gid);
}
