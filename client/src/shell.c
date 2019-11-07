#include <shell.h>
#include <dispatch.h>
#include <status.h>
#include <extra/quote.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

static int construct_argv(char *line, int *argc, char ***argv)
{
	/* Temporary copy of line, because strsep() mangles it */
	char *buf = strdup(line);
	if (!buf)
		goto error_resources;

	char *saveptr = NULL;
	char *tok = NULL;
	size_t ntokens = 0;

	/* Count number of tokens */
	for (tok = strtok_r(buf, " ", &saveptr); tok;
	     tok = strtok_r(NULL, " ", &saveptr)) {
		ntokens++;
	}
	free(buf);

	char **tokens = malloc(ntokens * sizeof(char *));
	if (!tokens)
		goto error_resources;

	/* Iterate over the tokens in line and dynamically add them to tokens
	 * pointer array. */
	saveptr = NULL;
	buf = strdup(line);
	if (!buf)
		goto error_tokens;

	int i = 0;
	for (tok = strtok_r(buf, " ", &saveptr); tok;
	     tok = strtok_r(NULL, " ", &saveptr)) {
		tokens[i] = strdup(tok);
		i++;
	}
	free(buf);

	*argc = ntokens;
	*argv = tokens;
	return 0;

error_tokens:
	if (tokens)
		free(tokens);
error_resources:
	error("Failed to allocate required system resources.\n");
	return -ENOMEM;
}

int shell(void)
{
	/* Redirect stderr to stdout. This ensure thats errors are printed
	 * dynamically as output in the shell. */
	dup2(1, 2);

	/* Starting shell. */
	print_quote();
	for (;;) {
		printf(LBLUE "[implant]> " NONE);

		/* Read command. */
		char *command = NULL;
		size_t tmp = 0;
		int ret = getline(&command, &tmp, stdin);
		if (ret < 0) {
			error("Failed to read command.\n");
			return -errno;
		}

		/* Strip newline. */
		if (command[ret - 1] == '\n')
			command[ret - 1] = '\0';

		/* Construct argument array. */
		int argc;
		char **argv;
		ret = construct_argv(command, &argc, &argv);
		if (ret) {
			free(command);
			break;
		}

		if (argc == 0)
			continue;

		/* Catch quit command before dispatch. */
		if (strcmp("quit", argv[0]) == 0) {
			free(argv);
			free(command);
			break;
		}

		/* Dispatch command to be handled. */
		ret = dispatch(argc, argv);
		if (ret) {
			char *help_args[] = { "help", argv[0] };
			dispatch(2, help_args);
		}

		/* Free memory for handling this current command. */
		for (int i = 0; i < argc; i++)
			free(argv[i]);
		free(argv);
		free(command);
	}

	return 0;
}
