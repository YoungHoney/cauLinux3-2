#include "nll.h"

#define NUM_THREADS 4
static struct task_struct *threads[NUM_THREADS];
static int ranges[4][2] = {{0,24},{25,49},{50,74},{75,99}};

static int thread_func(void* data) 
{




    int *range_bound=(int *)data;
    add_to_list(current->cpu,range_bound);
    //search_list(thread_id,null,range);
    
    
    return 0;


}


static int __init ll_module_init(void) {

    int i;
    printk(KERN_INFO "20191155 gwakyounghun Entering Spinlock Module\n");
    

    init_my_list();

    for(i=0;i<NUM_THREADS;i++)
    {
	    threads[i]=kthread_run(thread_func,ranges[i],"gwakThread %d ",i);
    }

 

    return 0;
    
}

static void __exit ll_module_cleanup(void) {

	int i;
    printk(KERN_INFO "byebye gwak \n");


      printk(KERN_INFO "byebye gwak\n");
      for (i = 0; i < NUM_THREADS; i++) {
          if (threads[i]) {
              printk(KERN_INFO "im going %d\n",i);
              kthread_stop(threads[i]);
//              cleanup_my_list(i);
          }

      }




    printk(KERN_INFO "real bye 20191155 gwakyounghun\n");
}




module_init(ll_module_init);
module_exit(ll_module_cleanup); // 여기 수정
MODULE_LICENSE("GPL");

