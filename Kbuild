MODNAME ?= implant

ccflags-y := -I$(src)/include

obj-m := $(MODNAME).o

# add c files
SRCS += src/implant.c

OBJS := $(SRCS:.c=.o)

$(MODNAME)-y := $(OBJS)
