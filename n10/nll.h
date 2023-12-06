#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/kthread.h>
#include <linux/slab.h>
#include <linux/spinlock.h>
#include <linux/mutex.h>




struct my_node {
	struct list_head list;
	int data;
	int t_id;
};
extern spinlock_t my_lock;
extern struct mutex my_mutex;
extern struct my_node my_list;


void *add_to_list(int,int*);
int search_list(int,void*,int*);
int delete_from_list(int,int*);
void init_my_list(void);

