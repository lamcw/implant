#include <status.h>
#include <log.h>
#include <module/disinfect.h>

#include <syscall.h>
#include <errno.h>

#ifndef MODNAME
#define MODNAME "implant"
#endif /* MODNAME */

static int disinfect(void)
{
	int ret = syscall(__NR_delete_module, MODNAME, 0);

	if (ret) {
		IMLOG_DEBUG("Failed to unload the kernel module");
		if (errno)
			error("Disinfect requires root privilege.\n");
	} else {
		alert("Disinfect successful.\n");
	}

	return ret;
}

int disinfect_command_handler(int argc, char **argv)
{
	/* TODO: There should be supported arguments for this command. */
	(void)argc;
	(void)argv;

	return disinfect();
}
