#pragma once

#include <sys/types.h>

int privilege_set(pid_t pid, int perm);
