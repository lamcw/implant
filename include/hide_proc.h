#ifndef HIDE_PROC_H
#define HIDE_PROC_H

#include <stdbool.h>

int hide_proc_init(void);
int hide_proc_exit(void);
int hide_proc(const char *);
int unhide_proc(const char *);
bool is_proc_hidden(const char *);

#endif /* HIDE_PROC_H */
