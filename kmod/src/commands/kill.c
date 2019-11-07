#include <linux/kernel.h>

#include "log.h"
#include "commands/kill.h"
#include "proc_kill.h"

int kill_handler(int argc, char **argv)
{
	pid_t pid;
	int ret;

	if (argc < 2) {
		IMLOG_WARNING("pid not provided\n");
		return -EINVAL;
	}

	ret = kstrtoint(argv[1], 10, &pid);
	if (ret)
		return ret;

	return proc_kill(pid);
}
