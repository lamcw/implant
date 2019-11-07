#ifndef _PROC_HIDE_H
#define _PROC_HIDE_H

#include <stdbool.h>

int proc_hide_init(void);
int proc_hide_exit(void);
int proc_hide_add(const char *proc_name);
int proc_hide_remove(const char *proc_name);
bool is_proc_hidden(const char *proc_name);

#endif /* _PROC_HIDE_H */
