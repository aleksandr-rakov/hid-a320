###########################################################################
#
#
#       Makefile  --  modem kernel drivers Makefile.
#
#       Copyright(c) 2003, Smart Link Ltd. (www.smlink.com)
#	All rights reserved.
#
#       Author: Sasha K (sashak@smlink.com)
#
#
###########################################################################
#	Edited by aleksandr.rakov@gmail.com 20.08.2012
#	Now is Lenovo Ideacentre A320 keyboard makefile
###########################################################################

KERNEL_VER?=$(shell uname -r)

KERNEL_DIR:=/lib/modules/$(KERNEL_VER)/build

EXTRA_CFLAGS = -I$(obj)

obj-m:= hid-a320.o

module-dir:=${DESTDIR}/lib/modules/$(KERNEL_VER)/extra

all:
	@echo "	obj-m=$(obj-m)"
	$(MAKE) modules -C $(KERNEL_DIR) SUBDIRS=$(shell pwd)
	@echo "	finished all:"

install:
	install -D -m 644 hid-a320.ko $(module-dir)/hid-a320.ko
	/sbin/depmod -a

uninstall:
	rm -f $(module-dir)/hid-a320.ko
	modprobe -r hid-a320 ; echo -n
	/sbin/depmod -a

dep:

clean:
	$(RM) $(obj-m) $(obj-m:.o=.ko) *.mod.* .*.cmd *~ modules.order Module.symvers
	$(RM) -r .tmp_versions
