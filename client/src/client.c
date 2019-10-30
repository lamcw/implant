#include <debug.h>
#include <commands.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>

void usage(char *prog_name)
{
	printf(
			"usage: %s <COMMAND>\n"
			"List of main commands:\n"
			"install   \tInstall the implant to the system\n"
			"uninstall \tUninstall the implant from the system\n"
			"privilege \tModify the privilege of a running program with --pid and --perm\n"
			"List of common flags:\n"
			"--erase   \tErases the binary after performing the operation\n",
			prog_name);
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		IMLOG_DEBUG("The required number of arguments were not provided");
		goto f;
	}

	int ret = commands_dispatch(argc, argv);
	if (ret) {
		IMLOG_DEBUG("Failed to dispatch and handle the command");
		goto f;
	}

	return EXIT_SUCCESS;

f:
	usage(*argv);
	return EXIT_FAILURE;
}
