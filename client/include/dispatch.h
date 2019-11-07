#ifndef _DISPATCH_H
#define _DISPATCH_H

typedef int(command_handler_t)(int argc, char **argv);

int dispatch(int argc, char **argv);

#endif /* _DISPATCH_H */
