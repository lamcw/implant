#include <linux/types.h>
#include <linux/sched/signal.h>
#include <linux/sched.h>
#include <linux/version.h>
#include <asm/signal.h>
#include <asm-generic/siginfo.h>

#include "proc_kill.h"
#include "proc_uidgid.h"

int proc_kill(pid_t pid)
{
	int signum = SIGKILL;
#if LINUX_VERSION_CODE < KERNEL_VERSION(4, 20, 0)
	struct siginfo info;
#else
	struct kernel_siginfo info;
#endif
	struct task_struct *task = find_task_from_pid(pid);
	if (!task)
		return -ESRCH;
#if LINUX_VERSION_CODE < KERNEL_VERSION(4, 20, 0)
	memset(&info, 0, sizeof(struct siginfo));
#else
	memset(&info, 0, sizeof(struct kernel_siginfo));
#endif
	info.si_signo = signum;

	return send_sig_info(signum, &info, task);
}
