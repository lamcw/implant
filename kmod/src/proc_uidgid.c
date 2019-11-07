#include <linux/cred.h>
#include <linux/kernel.h>
#include <linux/pid.h>
#include <linux/sched.h>
#include <linux/uidgid.h>

#include "log.h"
#include "proc_uidgid.h"

void set_new_uid(struct cred *c, u_int target_uid)
{
	kuid_t new_uid = KUIDT_INIT(target_uid);
	c->uid = new_uid;
	c->euid = new_uid;
}

void set_new_gid(struct cred *c, u_int target_gid)
{
	kgid_t new_gid = KGIDT_INIT(target_gid);
	c->gid = new_gid;
	c->egid = new_gid;
}

struct task_struct *find_task_from_pid(int pid)
{
	struct pid *task_pid;
	struct task_struct *task;

	task_pid = find_vpid(pid);
	if (task_pid == NULL) {
		IMLOG_WARNING("Did not find pid struct from pid %d\n", pid);
		return NULL;
	}

	task = pid_task(task_pid, PIDTYPE_PID);
	return task;
}

void proc_set_uid(int pid, unsigned int uid)
{
	struct task_struct *task;
	task = find_task_from_pid(pid);

	if (task != NULL) {
		set_new_uid((struct cred *)task->cred, uid);
		set_new_uid((struct cred *)task->real_cred, uid);
	}
}

void proc_set_gid(int pid, unsigned int gid)
{
	struct task_struct *task;
	task = find_task_from_pid(pid);

	if (task != NULL) {
		set_new_gid((struct cred *)task->cred, gid);
		set_new_gid((struct cred *)task->real_cred, gid);
	}
}

void proc_unset_uid(int pid)
{
	struct task_struct *task;
	task = find_task_from_pid(pid);

	if (task != NULL) {
		set_new_uid((struct cred *)task->cred, task->cred->suid.val);
		set_new_uid((struct cred *)task->real_cred,
			    task->real_cred->suid.val);
	}
}

void proc_unset_gid(int pid)
{
	struct task_struct *task;
	task = find_task_from_pid(pid);

	if (task != NULL) {
		set_new_gid((struct cred *)task->cred, task->cred->sgid.val);
		set_new_gid((struct cred *)task->real_cred,
			    task->real_cred->sgid.val);
	}
}
