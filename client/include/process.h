#pragma once

#include <sys/types.h>

int modify_proc(char *cmd, pid_t pid);
int exec_proc(char *args);
