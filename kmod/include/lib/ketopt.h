#ifndef _KETOPT_H
#define _KETOPT_H

#include <linux/string.h> /* for strchr() and strncmp() */

#define ko_no_argument 0
#define ko_required_argument 1
#define ko_optional_argument 2

typedef struct {
	/**
	 * @ind: Equivalent to optind.
	 */
	int ind;
	/**
	 * @opt: Equivalent to optopt.
	 */
	int opt; /* equivalent to optopt */
	/**
	 * @arg: Equivalent to optarg.
	 */
	char *arg;
	/**
	 * @longidx: index of a long option; or -1 if short
	 */
	int longidx;
	/* private: internal use only */
	int i, pos, n_args;
} ketopt_t;

typedef struct {
	char *name;
	int has_arg;
	int val;
} ko_longopt_t;

const static ketopt_t KETOPT_INIT = { 1, 0, 0, -1, 1, 0, 0 };
const static ketopt_t KETOPT_INIT_ZERO = {
	1, 0, 0, -1, 0, 0, 0
}; /* This struct does not ignore argv[0] */

int ketopt(ketopt_t *s, int argc, char *argv[], int permute, const char *ostr,
	   const ko_longopt_t *longopts);

#endif /* _KETOPT_H */
