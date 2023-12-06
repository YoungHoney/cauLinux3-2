obj-m += gwakll.o 

gwakll-objs += ll.o gwaka.o calclock.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)



default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

