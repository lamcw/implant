#include <commands.h>
#include <debug.h>
#include <install.h>
#include <util.h>
#include <privilege.h>

#include <stdbool.h>
#include <sys/types.h>
#include <stdlib.h>

int commands_privilege_handler(int argc, char **argv)
{
	pid_t pid = -1;
	int perm = -1;

	bool erase_flag = false;

	int c;
	ketopt_t o = KETOPT_INIT;
	while ((c = ketopt(&o, argc, argv, 1, "", privilege_longopts)) >= 0) {
		switch (c) {
		case OPT_PRIVILEGE_PID:
			if (o.arg) {
				/* Error detection is for the weak. */
				pid = atoi(o.arg);
			}
			break;
		case OPT_PRIVILEGE_PERM:
			if (o.arg) {
				perm = atoi(o.arg);
			}
			break;
		case OPT_PRIVILEGE_ERASE:
			erase_flag = true;
			break;
		default:
			break;
		}
	}

	if (pid == -1 || perm == -1) {
		fprintf(stderr, "error: --pid and --perm must be provided with valid values\n");
		return -1;
	}

	/* Set privilege. */
	int ret = privilege_set(pid, perm);
	if (ret) {
		return ret;
	}

	/* Erase. */
	if (erase_flag) {
		ret = erase();
		if (ret) {
			IMLOG_WARN("Failed to erase the running program");
		}
	}

	return ret;
}



int commands_install_handler(int argc, char **argv)
{
	bool erase_flag = false;

	int c;
	ketopt_t o = KETOPT_INIT;
	while ((c = ketopt(&o, argc, argv, 1, "", install_longopts)) >= 0) {
		switch (c) {
		case OPT_INSTALL_ERASE:
			erase_flag = true;
			break;
		default:
			break;
		}
	}

	/* Install. */
	int ret = install();
	if (ret) {
		return ret;
	}

	/* Erase. */
	if (erase_flag) {
		ret = erase();
		if (ret) {
			IMLOG_WARN("Failed to erase the running program");
		}
	}

	return ret;
}

int commands_uninstall_handler(int argc, char **argv)
{
	bool erase_flag = false;

	int c;
	ketopt_t o = KETOPT_INIT;
	while ((c = ketopt(&o, argc, argv, 1, "", install_longopts)) >= 0) {
		switch (c) {
		case OPT_INSTALL_ERASE:
			erase_flag = true;
			break;
		default:
			break;
		}
	}

	/* Uninstall. */
	int ret = uninstall();
	if (ret) {
		return ret;
	}

	/* Erase. */
	if (erase_flag) {
		ret = erase();
		if (ret) {
			IMLOG_WARN("Failed to erase the running program");
		}
	}

	return ret;
}

int commands_dispatch(int argc, char **argv)
{

	int c;
	ketopt_t o = KETOPT_INIT;
	/* Read until the first command. */
	while ((c = ketopt(&o, argc, argv, 0, "", 0)) >= 0);

	if (o.ind == argc) {
		IMLOG_DEBUG("Failed to find command");
		return -1;
	}

	char *cmd = argv[o.ind];

	if (strcmp("install", cmd) == 0) {
		return commands_install_handler(argc, argv);
	} else if (strcmp("uninstall", cmd) == 0) {
		return commands_uninstall_handler(argc, argv);
	} else if (strcmp("privilege", cmd) == 0) {
		return commands_privilege_handler(argc, argv);
	} else {
		IMLOG_DEBUG("Command not recognised");
		return -1;
	}
}