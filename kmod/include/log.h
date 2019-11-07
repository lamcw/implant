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
#ifndef _LOG_H
#define _LOG_H

#include <linux/kernel.h>
#include <linux/module.h>

/* Available log levels. */
#define IMLOG_LEVEL_EMERG 0
#define IMLOG_LEVEL_ALERT 1
#define IMLOG_LEVEL_CRIT 2
#define IMLOG_LEVEL_ERR 3
#define IMLOG_LEVEL_WARNING 4
#define IMLOG_LEVEL_NOTICE 5
#define IMLOG_LEVEL_INFO 6
#define IMLOG_LEVEL_DEBUG 7
#define IMLOG_LEVEL_NONE 8

#ifndef IMLOG_LEVEL
/* Logging is disabled by default. */
#define IMLOG_LEVEL IMLOG_LEVEL_NONE
#endif /* IMLOG_LEVEL */

#define IMLOG_DEBUG(fmt, ...)                                                  \
	printk(KERN_DEBUG "%s: %s:%s:%d\t" fmt, THIS_MODULE->name, __FILE__,   \
	       __func__, __LINE__, ##__VA_ARGS__);
#define IMLOG_INFO(fmt, ...)                                                   \
	printk(KERN_INFO "%s: %s:%s:%d\t" fmt, THIS_MODULE->name, __FILE__,    \
	       __func__, __LINE__, ##__VA_ARGS__);
#define IMLOG_NOTICE(fmt, ...)                                                 \
	printk(KERN_NOTICE "%s: %s:%s:%d\t" fmt, THIS_MODULE->name, __FILE__,  \
	       __func__, __LINE__, ##__VA_ARGS__);
#define IMLOG_WARNING(fmt, ...)                                                \
	printk(KERN_WARNING "%s: %s:%s:%d\t" fmt, THIS_MODULE->name, __FILE__, \
	       __func__, __LINE__, ##__VA_ARGS__);
#define IMLOG_ERR(fmt, ...)                                                    \
	printk(KERN_ERR "%s: %s:%s:%d\t" fmt, THIS_MODULE->name, __FILE__,     \
	       __func__, __LINE__, ##__VA_ARGS__);
#define IMLOG_CRIT(fmt, ...)                                                   \
	printk(KERN_CRIT "%s: %s:%s:%d\t" fmt, THIS_MODULE->name, __FILE__,    \
	       __func__, __LINE__, ##__VA_ARGS__);
#define IMLOG_ALERT(fmt, ...)                                                  \
	printk(KERN_ALERT "%s: %s:%s:%d\t" fmt, THIS_MODULE->name, __FILE__,   \
	       __func__, __LINE__, ##__VA_ARGS__);
#define IMLOG_EMERG(fmt, ...)                                                  \
	printk(KERN_EMERG "%s: %s:%s:%d\t" fmt, THIS_MODULE->name, __FILE__,   \
	       __func__, __LINE__, ##__VA_ARGS__);

#if IMLOG_LEVEL > IMLOG_LEVEL_EMERG
#undef IMLOG_EMERG
#define IMLOG_EMERG(fmt, ...)                                                  \
	do {                                                                   \
	} while (0)
#endif

#if IMLOG_LEVEL > IMLOG_LEVEL_ALERT
#undef IMLOG_ALERT
#define IMLOG_ALERT(fmt, ...)                                                  \
	do {                                                                   \
	} while (0)
#endif

#if IMLOG_LEVEL > IMLOG_LEVEL_CRIT
#undef IMLOG_CRIT
#define IMLOG_CRIT(fmt, ...)                                                   \
	do {                                                                   \
	} while (0)
#endif

#if IMLOG_LEVEL > IMLOG_LEVEL_ERR
#undef IMLOG_ERR
#define IMLOG_ERR(fmt, ...)                                                    \
	do {                                                                   \
	} while (0)
#endif

#if IMLOG_LEVEL > IMLOG_LEVEL_WARNING
#undef IMLOG_WARNING
#define IMLOG_WARNING(fmt, ...)                                                \
	do {                                                                   \
	} while (0)
#endif

#if IMLOG_LEVEL > IMLOG_LEVEL_NOTICE
#undef IMLOG_NOTICE
#define IMLOG_NOTICE(fmt, ...)                                                 \
	do {                                                                   \
	} while (0)
#endif

#if IMLOG_LEVEL > IMLOG_LEVEL_INFO
#undef IMLOG_INFO
#define IMLOG_INFO(fmt, ...)                                                   \
	do {                                                                   \
	} while (0)
#endif

#if IMLOG_LEVEL > IMLOG_LEVEL_DEBUG
#undef IMLOG_DEBUG
#define IMLOG_DEBUG(fmt, ...)                                                  \
	do {                                                                   \
	} while (0)
#endif

#endif /* _LOG_H */
