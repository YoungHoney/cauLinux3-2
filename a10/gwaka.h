// gwaka.h

#include <linux/list.h>
#include <linux/spinlock.h>
#include <linux/slab.h>
#include "calclock.h"

extern unsigned long long add_time;
extern unsigned long long search_time;
extern unsigned long long delete_time;

extern unsigned long long add_count;
extern unsigned long long search_count;
extern unsigned long long delete_count;

// Define your struct here
struct my_node {
    int data;
    int thread_id;
    struct list_head list;
};

// Declare the spinlock and the list
extern spinlock_t my_lock;
extern struct my_node my_list;
// Function prototypes
void add_to_list(int thread_id, int range_bound[]);
int search_list(int,void*,int*);
int delete_from_list(int,int*);
