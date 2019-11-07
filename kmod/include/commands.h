#ifndef _COMMANDS_H
#define _COMMANDS_H

/**
 * typedef command_handler_t - command handler function
 *
 * A command handler should take in argc and argv.
 */
typedef int(command_handler_t)(int argc, char **argv);

int commands_dispatch(int argc, char **argv);

#endif /* _COMMANDS_H */
