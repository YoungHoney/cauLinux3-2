// gwaka.h

#include <linux/list.h>
#include <linux/spinlock.h>
#include <linux/slab.h>
#include "calclock.h"

// Define your struct here
struct my_list_node {
    int data;
    struct list_head list;
};

// Declare the spinlock and the list
extern spinlock_t my_lock;
extern struct list_head my_list;

// Function prototypes
void add_to_list(int thread_id, int range_bound[]);
void init_my_list(void);
void cleanup_my_list(void);
int search_list(int,void*,int*);
int delete_from_list(int,int*);
