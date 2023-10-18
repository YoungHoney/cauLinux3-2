#include <linux/syscalls.h>

SYSCALL_DEFINE0(mycall)
{
	printk("System Call Example 20191155gwakyounghun\n");
	return 0;
}
