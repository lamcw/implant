#include <asm-generic/errno-base.h>

#include "commands/unhide.h"
#include "lib/ketopt.h"
#include "proc_hide.h"
#include "log.h"

enum { opt_unhide_pid,
       opt_unhide_file,
};

const static ko_longopt_t longopts[] = {
	{ "pid", ko_required_argument, opt_unhide_pid },
	{ "file", ko_required_argument, opt_unhide_file },
	{ NULL, 0, 0 }
};

int unhide_handler(int argc, char **argv)
{
	ketopt_t o = KETOPT_INIT;
	int err = 0;
	int ret;
	int c;

	while ((c = ketopt(&o, argc, argv, 1, "", longopts)) >= 0) {
		switch (c) {
		case opt_unhide_pid:
			if (o.arg) {
				ret = proc_hide_remove(o.arg);
				if (ret) {
					IMLOG_WARNING("%s cannot be unhidden\n",
						      o.arg);
					err++;
				}
			} else {
				err++;
			}
			break;
		case opt_unhide_file:
			break;
		}
	}

	return err ? -EINVAL : 0;
}
