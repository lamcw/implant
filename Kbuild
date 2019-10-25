MODNAME ?= implant

ccflags-y := -I$(src)/include

obj-m := $(MODNAME).o

# add c files
SRCS += src/implant.c
SRCS += src/privilege_escalation.c
SRCS += src/hide_proc.c

OBJS := $(SRCS:.c=.o)

$(MODNAME)-y := $(OBJS)
