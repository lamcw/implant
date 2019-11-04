#include "log.h"
#include "userland_exec.h"

int bash_exec(char *command)
{
	char *argv[] = { "/bin/bash", "-c", command, NULL };
	IMLOG_INFO("Calling bash exec with %s\n", command);
	return user_exec(argv);
}

int user_exec(char **argv)
{
	struct subprocess_info *info;
	char *envp[] = { PATH, NULL };

	info = call_usermodehelper_setup(argv[0], argv, envp, GFP_KERNEL, NULL,
					 NULL, NULL);
	if (info == NULL)
		return -ENOMEM;

	call_usermodehelper_exec(info, UMH_WAIT_EXEC);

	return info->pid;
}
