#include "nll.h"



spinlock_t my_lock;
struct mutex my_mutex;


struct my_node my_list;



void *add_to_list(int thread_id, int range_bound[])
{

	int i;
	struct my_node *new_node;

	thread_id=current->cpu;


	printk(KERN_INFO "thread #%d range: %d ~ %d\n",
			thread_id, range_bound[0], range_bound[1]);

	spin_lock(&my_lock);
	    for(i = range_bound[0]; i <= range_bound[1]; i++) {
                new_node = kmalloc(sizeof(*new_node), GFP_KERNEL);
                new_node->data = i;
	        new_node->t_id=thread_id;

	        
		list_add_tail(&new_node->list, &my_list.list);
		
	    }
	spin_unlock(&my_lock);

	printk(KERN_INFO "thread #%d adding complete\n",thread_id);




	return new_node;
}

int search_list(int thread_id, void *data, int range_bound[])
{
	struct timespec localclock[2];

	struct my_node *cur=(struct my_node *) data, *tmp;


	mutex_lock(&my_mutex);





	mutex_unlock(&my_mutex);



	return 0;
}

int delete_from_list(int thread_id, int range_bound[])
{
	struct my_node *cur, *tmp;
	struct timespec localclock[2];

	return 0;
}


void init_my_list(void) {
	spin_lock_init(&my_lock);
        mutex_init(&my_mutex);



	INIT_LIST_HEAD(&my_list.list);
}
