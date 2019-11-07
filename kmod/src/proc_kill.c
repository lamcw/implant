#include <linux/types.h>
#include <linux/sched/signal.h>
#include <linux/sched.h>
#include <asm/signal.h>
#include <asm-generic/siginfo.h>

#include "proc_kill.h"
#include "proc_uidgid.h"

int proc_kill(pid_t pid)
{
	int signum = SIGKILL;
	struct siginfo info;
	struct task_struct *task = find_task_from_pid(pid);
	if (!task)
		return -ESRCH;
	memset(&info, 0, sizeof(struct siginfo));
	info.si_signo = signum;

	return send_sig_info(signum, &info, task);
}
