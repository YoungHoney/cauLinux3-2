#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/kthread.h> // kthread_run을 위해 필요
#include "gwaka.h"



static int __init ll_module_init(void) {

    int i;
    printk(KERN_INFO "20191155 gwakyounghun Entering Spinlock Module\n");

    return 0;
    
}

static void __exit ll_module_cleanup(void) {

    printk(KERN_INFO "byebye gwak \n");

}

module_init(ll_module_init);
module_exit(ll_module_cleanup); // 여기 수정
MODULE_LICENSE("GPL");

