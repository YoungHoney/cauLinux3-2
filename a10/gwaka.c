// gwaka.c

#include "gwaka.h"

// Define your spinlock here
spinlock_t my_lock;

// Initialize your list here
struct my_node my_list;


unsigned long long add_time = 0;
unsigned long long search_time = 0;
unsigned long long delete_time = 0;

unsigned long long add_count = 0;
unsigned long long search_count = 0;
unsigned long long delete_count = 0;

void add_to_list(int thread_id, int range_bound[])
{
    int i;
    struct my_node *new_node;
    struct timespec stopwatch[2];
    getrawmonotonic(&stopwatch[0]);

    for(i = range_bound[0]; i <= range_bound[1]; i++) {
	new_node = kmalloc(sizeof(struct my_node), GFP_KERNEL);
        new_node->data = i;
        new_node->thread_id=thread_id;

	add_count++;
        list_add_tail(&new_node->list, &my_list.list);

    }

    getrawmonotonic(&stopwatch[1]);
    calclock(stopwatch, &add_time,&add_count);
    add_count--; //by calclock, add_count increase 1 but real object for add_count is for counting list element

    printk(KERN_INFO "thread #%d add range: %d ~ %d\n",
        thread_id, range_bound[0], range_bound[1]);
}




int search_list(int thread_id, void *data, int range_bound[])
{
    struct timespec localclock[2];
/* This will point on the actual data structures during the iteration */
    struct my_node *cur = (struct my_node *) data, *tmp;
    
    getrawmonotonic(&localclock[0]);
    list_for_each_entry_safe(cur,tmp,&my_list.list,list) {
        if(cur->data>=range_bound[0] && cur->data<=range_bound[1]){
	    search_count++;
//	    printk(KERN_INFO "search thread _id : %d and data : %d\n",thread_id, cur->data);
	    }
	}
   getrawmonotonic(&localclock[1]);
   calclock(localclock,&search_time,&search_count);
   search_count--;
    printk(KERN_INFO "thread # %d search range: %d ~ %d\n",
	   thread_id, range_bound[0], range_bound[1]); 
    return 0;
}




int delete_from_list(int thread_id, int range_bound[])
{
    struct my_node *cur, *tmp;
    struct timespec localclock2[2];

    getrawmonotonic(&localclock2[0]);

    list_for_each_entry_safe(cur,tmp,&my_list.list,list) {
	    if(cur->thread_id==thread_id) {
		delete_count++;    
//	        printk(KERN_INFO "delete thread _id : %d and data : %d\n",thread_id, cur->data);
		list_del(&cur->list);
		kfree(cur);
	    }
    }
    getrawmonotonic(&localclock2[1]);
    calclock(localclock2,&delete_time,&delete_count);
    delete_count--;

    

    printk(KERN_INFO "thread # %d deleted range : %d~%d\n",
		    thread_id, range_bound[0], range_bound[1]);
    return 0;
}


