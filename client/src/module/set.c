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
#include <grp.h>
#include <pwd.h>

enum { opt_set_uid, opt_set_gid };

static const ko_longopt_t set_longopts[] = {
	{ "uid", ko_required_argument, opt_set_uid },
	{ "gid", ko_required_argument, opt_set_gid },
	{ NULL, 0, 0 }
};

static int validate_uid(uid_t uid)
{
	struct passwd *tmp_passwd = getpwuid(uid);
	if (tmp_passwd == NULL) {
		switch (errno) {
		/* Resource errors. */
		case EINTR:
		case EIO:
		case EMFILE:
		case ENFILE:
		case ENOMEM:
		case ERANGE:
			error("Insufficient resources.\n");
			break;
		/* The given uid was not found. */
		default:
			error("The given uid was not found.\n");
			break;
		}

		/* It is possible that errno is 0. */
		if (errno)
			return -errno;
		else
			return -1;
	}

	alert("Validated uid.\n");
	return 0;
}

static int validate_gid(gid_t gid)
{
	struct group *tmp_group = getgrgid(gid);
	if (tmp_group == NULL) {
		switch (errno) {
		case EINTR:
		case EIO:
		case EMFILE:
		case ENFILE:
		case ENOMEM:
		case ERANGE:
			error("Insufficient resources.\n");
			break;
		/* The given gid was not found. */
		default:
			error("The given gid was not found.\n");
			break;
		}

		/* It is possible that errno is 0. */
		if (errno)
			return -errno;
		else
			return -1;
	}

	alert("Validated gid.\n");
	return 0;
}

static int set(pid_t pid, uid_t uid, bool set_uid, gid_t gid, bool set_gid)
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
		free(msg);
		goto f;
	}

	free(tmp);
	if (set_uid) {
		ret = validate_uid(uid);
		if (ret)
			return ret;

		char *tmp;
		ret = asprintf(&tmp, "--uid %d ", uid);
		if (ret < 0)
			goto f;

		ret = dynstrcat(&msg, tmp);
		free(tmp);

		if (ret)
			goto f;
	}

	if (set_gid) {
		ret = validate_gid(gid);
		if (ret)
			return ret;

		char *tmp;
		ret = asprintf(&tmp, "--gid %d ", gid);
		if (ret < 0)
			goto f;

		ret = dynstrcat(&msg, tmp);
		free(tmp);

		if (ret)
			goto f;
	}

	ret = comm(msg, strlen(msg));
	free(msg);
	return ret;

f:
	error("Failed to allocate system resources.\n");
	free(msg);
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

	int ret = set(pid, uid, uid_provided, gid, gid_provided);

	return ret;
}
