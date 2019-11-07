#include "log.h"
#include "commands.h"
#include "commands/exec.h"
#include "commands/kill.h"
#include "commands/hide.h"
#include "commands/unhide.h"
#include "commands/ps.h"
#include "commands/ls.h"
#include "commands/set.h"
#include "commands/unset.h"

int commands_dispatch(int argc, char **argv)
{
	command_handler_t *handler = NULL;
	char *cmd = NULL;

	if (argv)
		cmd = argv[0];
	else
		IMLOG_WARNING("argv is NULL\n");

	if (strcmp("exec", cmd) == 0)
		handler = &exec_handler;
	else if (strcmp("kill", cmd) == 0)
		handler = &kill_handler;
	else if (strcmp("hide", cmd) == 0)
		handler = &hide_handler;
	else if (strcmp("unhide", cmd) == 0)
		handler = &unhide_handler;
	else if (strcmp("ps", cmd) == 0)
		handler = &ps_handler;
	else if (strcmp("ls", cmd) == 0)
		handler = &ls_handler;
	else if (strcmp("set", cmd) == 0)
		handler = &set_handler;
	else if (strcmp("unset", cmd) == 0)
		handler = &unset_handler;

	if (handler == NULL) {
		IMLOG_WARNING("Unknown command: %s\n", cmd);
		return -EINVAL;
	}

	return handler(argc, argv);
}
