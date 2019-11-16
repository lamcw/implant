#include <linux/kernel.h>
#include <linux/uidgid.h>
#include <asm-generic/errno-base.h>
#include <stdbool.h>

#include "command/unset.h"
#include "lib/ketopt.h"
#include "log.h"
#include "proc_uidgid.h"

enum { opt_unset_uid, opt_unset_gid };

const static ko_longopt_t longopts[] = {
	{ "uid", ko_no_argument, opt_unset_uid },
	{ "gid", ko_no_argument, opt_unset_gid },
	{ NULL, 0, 0 }
};

int unset_handler(int argc, char **argv)
{
	ketopt_t o = KETOPT_INIT;
	int ret;
	int c;
	int pid;

	if (argc > 1) {
		ret = kstrtoint(argv[1], 10, &pid);
		if (ret)
			return ret;
	} else {
		IMLOG_WARNING("No pid supplied\n");
		return -EINVAL;
	}

	while ((c = ketopt(&o, argc, argv, 1, "", longopts)) >= 0) {
		switch (c) {
		case opt_unset_uid:
			proc_unset_uid(pid);
			break;
		case opt_unset_gid:
			proc_unset_gid(pid);
			break;
		}
	}

	return 0;
}
