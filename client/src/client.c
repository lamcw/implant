#include <status.h>
#include <dispatch.h>
#include <shell.h>

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char *argv[])
{
	assert(argc >= 1);
	if (argc == 1)
		return shell();

	/* Dispatch does not need the name the program was called with.
	 * Arguments are provided as needed to know. */
	int ret = dispatch(argc - 1, &argv[1]);
	if (ret) {
		char *arg = "help";
		dispatch(1, &arg);
	}

	return ret;
}
