#ifndef _STATUS_H
#define _STATUS_H

#include <stdio.h>
#include <unistd.h>

/* ANSI colours. */
#define NONE "\x1b[0m"
#define BLACK "\x1b[0;30m"
#define LBLACK "\x1b[1;30m"
#define RED "\x1b[0;31m"
#define LRED "\x1b[1;31m"
#define GREEN "\x1b[0;32m"
#define LGREEN "\x1b[1;32m"
#define BROWN "\x1b[0;33m"
#define YELLOW "\x1b[1;33m"
#define BLUE "\x1b[0;34m"
#define LBLUE "\x1b[1;34m"
#define PURPLE "\x1b[0;35m"
#define LPURPLE "\x1b[1;35m"
#define CYAN "\x1b[0;36m"
#define LCYAN "\x1b[1;36m"
#define GRAY "\x1b[0;37m"
#define WHITE "\x1b[1;37m"

static inline void alert(const char *msg)
{
	printf(GREEN "[*] " LGREEN "%s" NONE, msg);
}

static inline void error(const char *msg)
{
	fprintf(stderr, RED "[*] " LRED "%s" NONE, msg);
}

#endif /* _ERROR_H */
