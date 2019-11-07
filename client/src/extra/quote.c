#include <status.h>
#include <extra/quote.h>

#include <stdlib.h>
#include <time.h>

void print_quote(void)
{
	time_t seed = time(NULL);
	srand(seed);

	const char *tmp = quote[rand() % NUM_QUOTE];
	alert(tmp);
}
