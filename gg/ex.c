#include <linux/module.h>
#include <linux/rculist.h>
#include <linux/slab.h>
#include <linux/rcupdate.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Simple RCU Example");

struct my_node {
    int data;
    struct list_head list;
};

static LIST_HEAD(my_list);

void add_node(int data) {
    struct my_node *node;

    node = kmalloc(sizeof(*node), GFP_KERNEL);
    if (!node)
        return;

    node->data = data;
    list_add_rcu(&node->list, &my_list);
}

void remove_node(int data) {
    struct my_node *node, *tmp;

    list_for_each_entry_safe(node, tmp, &my_list, list) {
        if (node->data == data) {
            list_del_rcu(&node->list);
            synchronize_rcu();
            kfree(node);
            break;
        }
    }
}

int show_data(void) {
    struct my_node *node;
    int data = -1;

    rcu_read_lock();
    list_for_each_entry_rcu(node, &my_list, list) {
        data = node->data;
        pr_info("Data: %d\n", data);
    }
    rcu_read_unlock();

    return data;
}

static int __init my_module_init(void) {
    pr_info("Module loaded\n");

    add_node(10);
    add_node(20);
    add_node(30);

    show_data();

    remove_node(20);

    show_data();

    return 0;
}

static void __exit my_module_exit(void) {
    struct my_node *node, *tmp;

    list_for_each_entry_safe(node, tmp, &my_list, list) {
        list_del_rcu(&node->list);
        kfree(node);
    }

    pr_info("Module unloaded\n");
}

module_init(my_module_init);
module_exit(my_module_exit);

