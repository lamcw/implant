#ifndef _COMM_H
#define _COMM_H

#include <sys/types.h>

#ifndef IMPLANT_DEVICE_NAME
#define IMPLANT_DEVICE_NAME "implant"
#endif

#ifndef IMPLANT_DEVICE_PATH
#define IMPLANT_DEVICE_PATH "/dev/" IMPLANT_DEVICE_NAME
#endif

int comm(const char *msg, size_t len);

#endif /* _COMM_H */
