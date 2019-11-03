/*
 * Copyright (c) 2019 Jasper Lowell
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include <stdio.h>

/* Available log levels. */
#define IMLOG_LEVEL_TRACE 1
#define IMLOG_LEVEL_DEBUG 2
#define IMLOG_LEVEL_INFO 3
#define IMLOG_LEVEL_WARN 4
#define IMLOG_LEVEL_ERROR 5
#define IMLOG_LEVEL_FATAL 6
#define IMLOG_LEVEL_NONE 7

#ifndef IMLOG_LEVEL
/* Logging is disabled by default. */
#define IMLOG_LEVEL IMLOG_LEVEL_NONE
#endif /* IMLOG_LEVEL */

/* ANSI colours. */
#define NONE "\x1b[0m"
#define BLACK "\x1b[0;30m"
#define L_BLACK "\x1b[1;30m"
#define RED "\x1b[0;31m"
#define L_RED "\x1b[1;31m"
#define GREEN "\x1b[0;32m"
#define L_GREEN "\x1b[1;32m"
#define BROWN "\x1b[0;33m"
#define YELLOW "\x1b[1;33m"
#define BLUE "\x1b[0;34m"
#define L_BLUE "\x1b[1;34m"
#define PURPLE "\x1b[0;35m"
#define L_PURPLE "\x1b[1;35m"
#define CYAN "\x1b[0;36m"
#define L_CYAN "\x1b[1;36m"
#define GRAY "\x1b[0;37m"
#define WHITE "\x1b[1;37m"

#define IMLOG_TRACE(fmt, ...)                                                  \
	fprintf(stderr,                                                        \
		GRAY "[TRACE]   "                                              \
		     "%s:%s:%d: " NONE fmt "\n",                               \
		__func__, __FILE__, __LINE__, ##__VA_ARGS__);
#define IMLOG_DEBUG(fmt, ...)                                                  \
	fprintf(stderr,                                                        \
		CYAN "[DEBUG]   "                                              \
		     "%s:%s:%d: " NONE fmt "\n",                               \
		__func__, __FILE__, __LINE__, ##__VA_ARGS__);
#define IMLOG_INFO(fmt, ...)                                                   \
	fprintf(stderr,                                                        \
		GREEN "[INFO]    "                                             \
		      "%s:%s:%d: " NONE fmt "\n",                              \
		__func__, __FILE__, __LINE__, ##__VA_ARGS__);
#define IMLOG_WARN(fmt, ...)                                                   \
	fprintf(stderr,                                                        \
		BLUE "[WARN]    "                                              \
		     "%s:%s:%d: " NONE fmt "\n",                               \
		__func__, __FILE__, __LINE__, ##__VA_ARGS__);
#define IMLOG_ERROR(fmt, ...)                                                  \
	fprintf(stderr,                                                        \
		RED "[ERROR]   "                                               \
		    "%s:%s:%d: " NONE fmt "\n",                                \
		__func__, __FILE__, __LINE__, ##__VA_ARGS__);
#define IMLOG_FATAL(fmt, ...)                                                  \
	fprintf(stderr,                                                        \
		PURPLE "[FATAL]   "                                            \
		       "%s:%s:%d: " NONE fmt "\n",                             \
		__func__, __FILE__, __LINE__, ##__VA_ARGS__);

#if IMLOG_LEVEL > IMLOG_LEVEL_TRACE
#undef IMLOG_TRACE
#define IMLOG_TRACE(fmt, ...)                                                  \
	do {                                                                   \
	} while (0)
#endif

#if IMLOG_LEVEL > IMLOG_LEVEL_DEBUG
#undef IMLOG_DEBUG
#define IMLOG_DEBUG(fmt, ...)                                                  \
	do {                                                                   \
	} while (0)
#endif

#if IMLOG_LEVEL > IMLOG_LEVEL_INFO
#undef IMLOG_INFO
#define IMLOG_INFO(fmt, ...)                                                   \
	do {                                                                   \
	} while (0)
#endif

#if IMLOG_LEVEL > IMLOG_LEVEL_WARN
#undef IMLOG_WARN
#define IMLOG_WARN(fmt, ...)                                                   \
	do {                                                                   \
	} while (0)
#endif

#if IMLOG_LEVEL > IMLOG_LEVEL_ERROR
#undef IMLOG_ERROR
#define IMLOG_ERROR(fmt, ...)                                                  \
	do {                                                                   \
	} while (0)
#endif

#if IMLOG_LEVEL > IMLOG_LEVEL_FATAL
#undef IMLOG_FATAL
#define IMLOG_FATAL(fmt, ...)                                                  \
	do {                                                                   \
	} while (0)
#endif
