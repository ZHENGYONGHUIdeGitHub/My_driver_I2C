KERN_DIR = /home/zhengyonghui/WorkSpace/Linux_kernel/linux-2.6.22.6

all:
	make -C $(KERN_DIR) M=`pwd` modules 

clean:
	make -C $(KERN_DIR) M=`pwd` modules clean
	rm -rf modules.order

obj-m	+= at24cxx.o
