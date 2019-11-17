#include <status.h>
#include <module/help.h>

#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum { help_module_infect,
       help_module_disinfect,
       help_module_exec,
       help_module_kill,
       help_module_hide,
       help_module_unhide,
       help_module_set,
       help_module_unset,
       help_module_payloads,
       help_module_help,
       help_module_done };

const char *const help[] = {
	"infect",
	"disinfect",
	"exec [--bash] [--hide] [--uid <uid>] [--gid <gid>] <command>",
	"kill <pid>",
	"hide [--pid <pid> | --module",
	"unhide [--pid <pid> | --module",
	"set <pid> [--uid <uid>] [--gid <gid>]",
	"unset <pid> [--uid] [--gid]",
	"payload [--list | --exec <name>]",
	"help <module>"
};

int help_command_handler(int argc, char **argv)
{
	if (argc == 1) {
		/* Print all help. */
		for (int i = 0; i < help_module_done; i++)
			puts(help[i]);
		return 0;
	}

	if (argc == 2) {
		/* Print help for the module provided as an argument. */
		const char *module = argv[1];
		if (strcmp(module, "infect") == 0)
			puts(help[help_module_infect]);
		else if (strcmp(module, "disinfect") == 0)
			puts(help[help_module_disinfect]);
		else if (strcmp(module, "exec") == 0)
			puts(help[help_module_exec]);
		else if (strcmp(module, "kill") == 0)
			puts(help[help_module_kill]);
		else if (strcmp(module, "hide") == 0)
			puts(help[help_module_hide]);
		else if (strcmp(module, "unhide") == 0)
			puts(help[help_module_unhide]);
		else if (strcmp(module, "set") == 0)
			puts(help[help_module_set]);
		else if (strcmp(module, "unset") == 0)
			puts(help[help_module_unset]);
		else if (strcmp(module, "payload") == 0)
			puts(help[help_module_payloads]);
		else if (strcmp(module, "help") == 0)
			puts(help[help_module_help]);
		else
			goto f;

		return 0;

	f:
		error("No help available for the module provided. Is that "
		      "module installed?\n");
		return -1;
	}

	error("Failed to parse command.\n");
	puts(help[help_module_help]);

	return 0;
}
