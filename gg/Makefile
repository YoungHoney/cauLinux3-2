obj-m += ex.o

# 경로는 실제 리눅스 커널 소스의 위치에 따라 달라질 수 있습니다.
# 현재 실행 중인 커널의 버전에 맞는 헤더 파일을 사용해야 합니다.
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)


default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

