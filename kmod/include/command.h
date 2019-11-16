#ifndef _COMMAND_H
#define _COMMAND_H

/**
 * typedef command_handler_t - command handler function
 *
 * A command handler should take in argc and argv.
 */
typedef int(command_handler_t)(int argc, char **argv);

int commands_dispatch(int argc, char **argv);

#endif /* _COMMAND_H */
