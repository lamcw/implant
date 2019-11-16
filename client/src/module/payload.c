#include <dlfcn.h>
#include <status.h>
#include <module/payload.h>
#include <lib/ketopt.h>
#include <lib/dynstr.h>
#include <payloads.h>

#include <stdbool.h>

enum { opt_payload_list, opt_payload_exec };

static const ko_longopt_t payload_longopts[] = {
	{ "list", ko_no_argument, opt_payload_list },
	{ "exec", ko_required_argument, opt_payload_exec },
	{ NULL, 0, 0 }
};

void *get_symbol(char *symbol)
{
	void *handle = dlopen(NULL, RTLD_LAZY);
	if (handle == NULL) {
		error("Failed to open handle required to find payload assets.\n");
		return handle;
	}

	void *addr = dlsym(handle, symbol);
	if (addr == NULL) {
		error("Failed to find payload assets.\n");
	}

	return addr;
}

void list_payloads()
{
	printf("Payloads installed:\n");
	for (int i = 0; payloads[i] != NULL; i++)
		printf(" - %s\n", payloads[i]);
}

int execute_payload(char *module_name)
{
	int ret;
	char *module_symbol_name = NULL;
	void *symbol;
	int (*fn)(void);

	ret = dynstrcat(&module_symbol_name, module_name);
	if (ret)
		goto f;

	ret = dynstrcat(&module_symbol_name, "_load");
	if (ret)
		goto f;

	symbol = get_symbol(module_symbol_name);
	if (symbol == NULL) {
		ret = -1;
		goto f;
	}

	fn = (int (*)(void))symbol;

	free(module_symbol_name);
	return fn();

f:
	if (module_symbol_name != NULL)
		free(module_symbol_name);
	return ret;
}

int payload_command_handler(int argc, char **argv)
{
	bool list = false;
	char *module = NULL;

	int c;
	ketopt_t o = KETOPT_INIT;
	while ((c = ketopt(&o, argc, argv, 1, "", payload_longopts)) >= 0) {
		switch (c) {
		case opt_payload_list:
			list = true;
			break;
		case opt_payload_exec:
			if (o.arg) {
				module = o.arg;
			}
			break;
		}
	}

	if (list == true && module != NULL) {
		error("Command flags --list and --exec are mutually exclusive.\n");
		return -1;
	}

	if (list == true) {
		list_payloads();
		return 0;
	}

	if (module != NULL)
		return execute_payload(module);

	error("Must provide either --list or --exec.\n");
	return -1;
}