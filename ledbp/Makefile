CARD_NUMB       = 23
ROUTER          = peri
LOGIN           = agon-lelouet
LAB             = lab2

MODULE          = ledbpAL

CROSSDIR        = /users/enseig/franck/IOC
KERNELDIR       = /dsk/l1/misc/agonlelouet/linux-rpi-3.18.y
CROSS_COMPILE   = $(CROSSDIR)/arm-bcm2708hardfp-linux-gnueabi/bin/bcm2708hardfp-

obj-m           += $(MODULE).o
default:;       make -C $(KERNELDIR) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) M=$(PWD) modules
clean:;         make -C $(KERNELDIR) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) M=$(PWD) clean
upload:;        scp -P622$(CARD_NUMB) $(MODULE).ko insdev rmdev blink pi@$(ROUTER):$(LOGIN)/$(LAB)
