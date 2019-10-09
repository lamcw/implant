#include <linux/module.h>

MODULE_DESCRIPTION("Implant");
MODULE_AUTHOR("sc");
MODULE_LICENSE("GPL");

static int __init implant_init(void)
{
	return 0;
}

static void __exit implant_exit(void)
{
}

module_init(implant_init);
module_exit(implant_exit);
