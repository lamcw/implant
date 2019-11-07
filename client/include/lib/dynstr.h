#ifndef _LIB_DYNSTR_H
#define _LIB_DYNSTR_H

#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>

static inline int dynstrcat(char **dynstrptr, const char *str)
{
	/* A pointer to char *dynstr is required to help prevent the use
	 * of stale pointers. This is conscious decision for defensive
	 * programming.
	 *
	 * The caller must ensure:
	 * 	char **dynstr must not be NULL.
	 *	char *str must not be NULL.
	 *
	 * Note that *dynstrptr is allowed to be NULL.
	 *
	 * Reallocating things on the heap like this is not preformant but the
	 * abstraction will hopefully prevent future bugs in caller code. */
	assert(dynstrptr != NULL);
	assert(str != NULL);

	/* If the dynstr does not exist, allocate memory for it. */
	if (*dynstrptr == NULL) {
		*dynstrptr = strdup(str);
		if (*dynstrptr == NULL) {
			return -errno;
		}

		return 0;
	}

	/* Extend the dynstr to fit str.
	 *
	 * It is not possible to check if a pointer points to a valid chunk
	 * on the heap. If dynstrcat is used improperly the code below may
	 * corrupt memory, corrupt the heap, or crash the program. */
	char *tmp = (char *)realloc(*dynstrptr,
				    strlen(*dynstrptr) + strlen(str) + 1);
	if (tmp == NULL)
		return -errno;

	*dynstrptr = tmp;
	strcat(*dynstrptr, str);
	return 0;
}

#endif /* _LIB_DYNSTR_H */
