#pragma once

#include <ketopt.h>

#define OPT_INSTALL_ERASE 101

/* Option used for install and uninstall. */
const static ko_longopt_t install_longopts[] = {
	{ "erase", ko_no_argument, OPT_INSTALL_ERASE },
	{ NULL, 0, 0}
};

int commands_dispatch(int argc, char **argv);
