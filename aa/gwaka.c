// gwaka.c

#include "gwaka.h"

// Define your spinlock here
spinlock_t my_lock;

// Initialize your list here
struct list_head my_list;

void add_to_list(int thread_id, int range_bound[])
{
    int i;
    struct my_list_node *new_node;

    for(i = range_bound[0]; i <= range_bound[1]; i++) {
        new_node = kmalloc(sizeof(*new_node), GFP_KERNEL);
        new_node->data = i;

        spin_lock(&my_lock);
        list_add_tail(&new_node->list, &my_list);
        spin_unlock(&my_lock);
    }

    printk(KERN_INFO "thread #%d range: %d ~ %d\n",
        thread_id, range_bound[0], range_bound[1]);
}

void init_my_list(void) {
    spin_lock_init(&my_lock);
    INIT_LIST_HEAD(&my_list);
}

void cleanup_my_list(void) {
    struct my_list_node *current_node, *next_node;

    list_for_each_entry_safe(current_node, next_node, &my_list, list) {
        list_del(&current_node->list);
        kfree(current_node);
    }
}

int search_list(int thread_id, void *data, int range_bound[])
{
    struct timespec localclock[2];
/* This will point on the actual data structures during the iteration */
    struct my_node *cur = (struct my_node *) data, *tmp;
// put your code here
    return 0;
}




int delete_from_list(int thread_id, int range_bound[])
{
    struct my_node *cur, *tmp;
    struct timespec localclock[2];
// put your code here
    return 0;
}



