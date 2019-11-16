#include <dispatch.h>
#include <log.h>
#include <status.h>

#include <module/infect.h>
#include <module/disinfect.h>
#include <module/exec.h>
#include <module/kill.h>
#include <module/hide.h>
#include <module/unhide.h>
#include <module/set.h>
#include <module/unset.h>
#include <module/help.h>
#include <module/payload.h>

#include <string.h>
#include <assert.h>

int dispatch(int argc, char **argv)
{
	assert(argc >= 1);
	assert(argv != NULL);
	assert(argv[0] != NULL);

	char *command = argv[0];
	command_handler_t *handler = NULL;

	if (strcmp("infect", command) == 0)
		handler = &infect_command_handler;
	else if (strcmp("disinfect", command) == 0)
		handler = &disinfect_command_handler;
	else if (strcmp("exec", command) == 0)
		handler = &exec_command_handler;
	else if (strcmp("kill", command) == 0)
		handler = &kill_command_handler;
	else if (strcmp("hide", command) == 0)
		handler = &hide_command_handler;
	else if (strcmp("unhide", command) == 0)
		handler = &unhide_command_handler;
	else if (strcmp("set", command) == 0)
		handler = &set_command_handler;
	else if (strcmp("unset", command) == 0)
		handler = &unset_command_handler;
	else if (strcmp("payload", command) == 0)
		handler = &payload_command_handler;
	else if (strcmp("help", command) == 0)
		handler = &help_command_handler;

	if (handler == NULL) {
		error("Command unrecognised.\n");
		return -1;
	}

	/* Handlers require the subcommand to be present. */
	return handler(argc, argv);
}
