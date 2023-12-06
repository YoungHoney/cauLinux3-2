#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h> // For current macro
#include <linux/kthread.h> // For kthreads
#include <linux/delay.h> // For ssleep()

#define NUM_THREADS 3
static struct task_struct *threads[NUM_THREADS];

int glob=0;
int counter=0;


// 스레드가 실행할 함수
static int gwak_cas_func(void* data) {
	int original;




	while(!kthread_should_stop()) {

	    while(__sync_val_compare_and_swap(&glob,0,1));	    
	    original=counter;
	    counter++;
	    printk(KERN_INFO "pid[%u] %s : counter : %d\n",
				current->pid, __func__, original);
	    glob=0;
	    
	    msleep(500);
	}
	do_exit(0);
}



int __init hello_module_init(void) {
    printk(KERN_INFO "20191155gwakyounghun gwakmodule init! \n");
    
    // 스레드를 생성하고 실행

    int i;
    

    for(i=0;i<NUM_THREADS;i++) {
	    threads[i]=kthread_run(gwak_cas_func,NULL,"thread%d",i);
    }

    return 0;
}

void __exit hello_module_cleanup(void) {
    printk(KERN_INFO "gwak young hun module good bye\n");
    
    // 스레드를 종료

    int i;

    for (i = 0; i < NUM_THREADS; i++) {
        if (threads[i])
            kthread_stop(threads[i]);
    }


}

module_init(hello_module_init);
module_exit(hello_module_cleanup);
MODULE_LICENSE("GPL");

