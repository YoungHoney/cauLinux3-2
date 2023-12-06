#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include "gwaka.h"
#include <linux/sched.h>
#include <linux/kthread.h> 
#include <linux/atomic.h>
#include <linux/delay.h>
#include <linux/mutex.h>
#include <linux/rwsem.h>
#define NUM_THREADS 4
struct task_struct *threads[NUM_THREADS];
int ranges[4][2] = {{0,249999},{250000,499999},{500000,749999},{750000,999999}};

atomic_t add_count4seq = ATOMIC_INIT(0);
atomic_t search_count4seq = ATOMIC_INIT(0);
atomic_t delete_count4seq = ATOMIC_INIT(0);

DECLARE_RWSEM(my_rwsem);

int *thread_id_args[NUM_THREADS]; // 각 쓰레드의 thread_id를 위한 배열

static int thread_function(void *data) {
    int thread_id = *(int *)data;

    down_write(&my_rwsem);
    add_to_list(thread_id, ranges[thread_id]); 
    up_write(&my_rwsem);
    atomic_inc(&add_count4seq);

    while(atomic_read(&add_count4seq)!=NUM_THREADS) {}
    down_read(&my_rwsem);
    search_list(thread_id, &my_list, ranges[thread_id]);
    up_read(&my_rwsem);
    atomic_inc(&search_count4seq);

    while (atomic_read(&search_count4seq) != NUM_THREADS) {}

    down_write(&my_rwsem);
    delete_from_list(thread_id, ranges[thread_id]);
    up_write(&my_rwsem);
    atomic_inc(&delete_count4seq);
 

    while (atomic_read(&delete_count4seq) != NUM_THREADS) {}

  
  while(!kthread_should_stop()) {
      msleep(500);
  }
    return 0;
}

static int __init ll_module_init(void) {
    int i;

    printk(KERN_INFO "REAL 20191155 gwakyounghun Entering rwsem Module\n");
    INIT_LIST_HEAD(&my_list.list);

    for (i = 0; i < NUM_THREADS; i++) {
        thread_id_args[i] = kmalloc(sizeof(int), GFP_KERNEL);
        *thread_id_args[i] = i;
        threads[i] = kthread_run(thread_function, thread_id_args[i], "thread-%d", i);
    }

    return 0;
}

static void __exit ll_module_cleanup(void) {
    int i;

    printk(KERN_INFO "Rwsem linked list insert time : %llu ns, count : %llu",add_time, add_count);
    printk(KERN_INFO "Rwsem linked list search time : %llu ns, count : %llu",search_time, search_count);
    printk(KERN_INFO "Rwsem linked list delete time : %llu ns, count : %llu",delete_time, delete_count); 
        


    for (i = 0; i < NUM_THREADS; i++) {
        
	printk(KERN_INFO "thread #%d stopped!\n", i);
        kthread_stop(threads[i]);
        kfree(thread_id_args[i]); // 각 쓰레드의 thread_id_arg 해제
    }
    printk(KERN_INFO "Exiting Rwsem Module! 20191155 gwakyounghun\n");  
}

module_init(ll_module_init);
module_exit(ll_module_cleanup);
MODULE_LICENSE("GPL");
