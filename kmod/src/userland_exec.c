#include <linux/umh.h>

#include "log.h"
#include "userland_exec.h"

#define PATH "/usr/local/bin:/usr/bin:/bin"

/** bash_exec() - Execute commands in bash shell.
 * @command: must be null-terminated
 *
 * Return: pid of the new process.
 */
pid_t bash_exec(char *command)
{
	char *argv[] = { "/bin/bash", "-c", command, NULL };
	IMLOG_INFO("Calling bash exec with \"%s\"\n", command);
	return user_exec(argv);
}

/** user_exec() - Wrapper for call_usermodehelper_(setup/exec)
 * @argv: arg vector for process
 *
 * Return: Either -ENOMEM on setup failture, or pid if successfully execute the
 * process
 */
pid_t user_exec(char **argv)
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
