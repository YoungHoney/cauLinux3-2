#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

int __init hello_module_init(void) {
	printk("gwakyounghun20191155 simple module\n");
	return 0;
}

void __exit hello_module_cleanup(void) {
	printk("gwakyounghun 20191155 goodbye\n");

}

module_init(hello_module_init);
module_exit(hello_module_cleanup);
MODULE_LICENSE("GPL");
