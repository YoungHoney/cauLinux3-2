#include <stdio.h>
#include <sys/syscall.h>

int main(void) {


	long ret=syscall(436);
	printf("20191155 gwak young hun : system call return : %ld\n",ret);

	return 0;
}
