#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/slab.h> // 메모리 할당을 위한 헤더

#define NUM_THREADS 4
static struct task_struct *threads[NUM_THREADS];

int glob = 0;
int counter = 0;
int end_checker = 0;



static int gwak_cas_func(void* data) {
    int *local_data; // 로컬 데이터 포인터

    // 메모리 할당
    local_data = kmalloc(sizeof(int), GFP_KERNEL);
    if (!local_data) {
        printk(KERN_ERR "Memory allocation failed\n");
        return -ENOMEM;
    }
    *local_data = 0; // 할당된 메모리 초기화

    while (!kthread_should_stop()) {
        while (__sync_lock_test_and_set(&glob, 1));

        (*local_data)++;
        counter++;
        printk(KERN_INFO "pid[%u] %s : counter : %d, local_data: %d\n",
               current->pid, __func__, counter, *local_data);
        glob = 0;

        msleep(500);
    }

    // 메모리 해제
    kfree(local_data);

    end_checker++;
    do_exit(0);
}

int __init hello_module_init(void) {
    int i;
    printk(KERN_INFO "20191155gwakyounghun gwakmodule init! \n");
    for (i = 0; i < NUM_THREADS; i++) {
        threads[i] = kthread_run(gwak_cas_func, NULL, "thread%d", i);
    }
    return 0;
}

void __exit hello_module_cleanup(void) {
    int i;
	for (i = 0; i < NUM_THREADS; i++) {
        if (threads[i])
            kthread_stop(threads[i]);
    }
    if (end_checker == NUM_THREADS) {
        printk(KERN_INFO "gwak young hun module good bye\n");
    }
}

module_init(hello_module_init);
module_exit(hello_module_cleanup);
MODULE_LICENSE("GPL");

