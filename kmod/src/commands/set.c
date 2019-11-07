#include <linux/kernel.h>
#include <linux/uidgid.h>

#include "commands/set.h"
#include "lib/ketopt.h"
#include "log.h"
#include "proc_uidgid.h"

enum { opt_set_uid, opt_set_gid };

const static ko_longopt_t longopts[] = {
	{ "uid", ko_required_argument, opt_set_uid },
	{ "gid", ko_required_argument, opt_set_gid },
	{ NULL, 0, 0 }
};

int set_handler(int argc, char **argv)
{
	ketopt_t o = KETOPT_INIT;
	int ret;
	int c;
	int pid;
	uid_t uid;
	gid_t gid;

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
		case opt_set_uid:
			if (o.arg) {
				ret = kstrtou32(o.arg, 10, &uid);
				if (ret)
					return ret;
				proc_set_uid(pid, uid);
			}
			break;
		case opt_set_gid:
			if (o.arg) {
				ret = kstrtou32(o.arg, 10, &gid);
				if (ret)
					return ret;
				proc_set_gid(pid, gid);
			}
			break;
		}
	}

	return 0;
}
