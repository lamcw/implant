#ifndef _USERLAND_EXEC_H
#define _USERLAND_EXEC_H

#include <linux/umh.h>

#define PATH "/usr/local/bin:/usr/bin:/bin"

int user_exec(char **);
int bash_exec(char *);

#endif /* _USERLAND_EXEC_H */