#ifndef _PRIVILEGE_ESCALATION_H
#define _PRIVILEGE_ESCALATION_H

#include <linux/cred.h>
#include <linux/kernel.h>
#include <linux/pid.h>
#include <linux/sched.h>
#include <linux/uidgid.h>

#define DEFAULT_CRED 0
#define INVALID_PID -1

void escalate_pid(int, int);
void descalate_pid(int);

#endif /* _PRIVILEGE_ESCALATION_H */