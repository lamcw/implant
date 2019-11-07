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

SRCS := $(wildcard $(src)/kmod/src/*.c) $(wildcard $(src)/kmod/src/*/*.c)
OBJS := $(patsubst $(src)/kmod/src/%.c,kmod/src/%.o,$(SRCS))

$(MODNAME)-y := $(OBJS)
