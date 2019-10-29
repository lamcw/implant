#ifndef _PRIVILEGE_ESCALATION_H
#define _PRIVILEGE_ESCALATION_H

#include <linux/cred.h>
#include <linux/kernel.h>
#include <linux/pid.h>
#include <linux/sched.h>
#include <linux/uidgid.h>

#define INVALID_PID (-1)

void root_creds(struct cred *);
struct task_struct *find_task_from_pid(int);
void escalate_pid(int);

#endif /* _PRIVILEGE_ESCALATION_H */