obj-m := myRand.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	$(CC) test.c -o test
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	rm test
