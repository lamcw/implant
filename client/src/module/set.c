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

enum { opt_set_uid, opt_set_gid };

static const ko_longopt_t set_longopts[] = {
	{ "uid", ko_required_argument, opt_set_uid },
	{ "gid", ko_required_argument, opt_set_gid },
	{ NULL, 0, 0 }
};

static int set_uid(pid_t pid, uid_t uid)
{
	char *msg = NULL;

	int ret = dynstrcat(&msg, "set ");
	if (ret)
		goto f;

	char *tmp;
	ret = asprintf(&tmp, "%d ", pid);
	if (ret < 0) {
		free(msg);
		goto f;
	}

	ret = dynstrcat(&msg, tmp);
	if (ret) {
		free(tmp);
		free(msg);
		goto f;
	}

	free(tmp);
	ret = asprintf(&tmp, "--uid %d ", uid);
	if (ret < 0) {
		free(msg);
		goto f;
	}

	ret = dynstrcat(&msg, tmp);
	if (ret) {
		free(tmp);
		free(msg);
		goto f;
	}

	free(tmp);
	ret = comm(msg, strlen(msg));
	free(msg);
	return ret;

f:
	error("Failed to allocate system resources.\n");
	return ret;
}

static int set_gid(pid_t pid, gid_t gid)
{
	char *msg = NULL;

	int ret = dynstrcat(&msg, "set ");
	if (ret)
		goto f;

	char *tmp;
	ret = asprintf(&tmp, "%d ", pid);
	if (ret < 0)
		goto f;

	ret = dynstrcat(&msg, tmp);
	if (ret) {
		free(tmp);
		goto f;
	}

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
	bool uid_provided = false;
	bool gid_provided = false;
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
				uid_provided = true;
				uid = atoi(o.arg);
			}
			break;
		case opt_set_gid:
			if (o.arg) {
				/* There is no good way to perform error
				 * detection here. The function strtol would
				 * need to be truncated. */
				gid_provided = true;
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
	if (pid == 0) {
		error("pid not parsed.\n");
		return -1;
	}

	if (!uid_provided && !gid_provided) {
		error("One of --uid or --gid is required.\n");
		return -1;
	}

	if (uid_provided) {
		int ret = set_uid(pid, uid);
		if (ret)
			return ret;
	}

	if (gid_provided)
		return set_gid(pid, gid);

	return 0;
}
