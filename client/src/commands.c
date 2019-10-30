#include <commands.h>
#include <debug.h>
#include <install.h>
#include <util.h>

#include <stdbool.h>

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
	} else {
		IMLOG_DEBUG("Command not recognised");
		return -1;
	}
}
