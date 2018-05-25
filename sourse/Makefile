# Comment/uncomment the following line to disable/enable debugging
#DEBUG = y


# Add your debugging flag (or not) to ccflags-y
ifeq ($(DEBUG),y)
  DEBFLAGS = -O -g  # "-O" is needed to expand inlines
else
  DEBFLAGS = -O2 -std=gnu89 --no-warning
endif

ccflags-y += $(DEBFLAGS)
ccflags-y += -I..

ifneq ($(KERNELRELEASE),)
# call from kernel build system

obj-m	:= nozero.o

else

KERNELDIR ?= /lib/modules/$(shell uname -r)/build
#KERNELDIR ?= /usr/src/linux-source-3.16
PWD       := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

endif



clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions

depend .depend dep:
	$(CC) $(ccflags-y) -M *.c > .depend


ifeq (.depend,$(wildcard .depend))
include .depend
endif
