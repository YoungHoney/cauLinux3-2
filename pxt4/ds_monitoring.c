#include "ds_monitoring.h"


void find_ds_monitoring(struct ds_monitoring *dm, void *elem)
{
	struct ds_monitoring_elem *cur;
	unsigned long xa_index;
	if (dm->dm_ops->get_index)
	{
		xa_index = dm->dm_ops->get_index(elem);
		// search ds_monitoring_elem at index of xa_index from xarray root
		cur = (struct ds_monitoring_elem *)xa_load(dm->elements, xa_index);
		if (cur)
		{
			__sync_fetch_and_add(&cur->count, 1);
		}
		else
		{
			insert_ds_monitoring(dm, xa_index, elem);
		}
		__sync_fetch_and_add(&dm->total_counts, 1);
	}
}

 void
insert_ds_monitoring(struct ds_monitoring *dm, unsigned long index, void *elem)
{
	char *name;
	struct ds_monitoring_elem *new = kmalloc(sizeof(struct ds_monitoring_elem), GFP_KERNEL);

	new->key = index;
	new->count = 1;

	if (dm->dm_ops->get_name)
	{
		name = dm->dm_ops->get_name(elem);
		new->name = kmalloc(strlen(name) + 1, GFP_KERNEL);
		strcpy(new->name, name);
	}
	else
	{
		new->name = NULL;
	}
	xa_store(dm->elements, new->key, (void *)new, GFP_KERNEL);
}

void print_ds_monitoring(struct ds_monitoring *dm)
{
	unsigned long cur_idx;
	void *cur;
	char *cur_name;
	unsigned long long cur_count;
	int percentage;

	if (!dm->total_counts)
		return;
	xa_for_each(dm->elements, cur_idx, cur)
	{
		cur_name = ((struct ds_monitoring_elem *)cur)->name;
		cur_count = ((struct ds_monitoring_elem *)cur)->count;
		percentage = (cur_count*100) / dm->total_counts;
		dm->dm_ops->print_elem(cur_idx, cur_name, cur_count, percentage);
	}
}

void delete_ds_monitoring(struct ds_monitoring *dm)
{
	unsigned long cur_idx;
	void *cur;
	char *cur_name;

	xa_for_each(dm->elements, cur_idx, cur)
	{
		cur_name = ((struct ds_monitoring_elem *)cur)->name;
		kfree(cur_name);
		kfree(cur);
	}
	xa_destroy(dm->elements);
}

unsigned long get_thread_idx(void *elem)
{
	int node_idx;
	unsigned long xa_index;
	int zone_idx;
	struct task_struct *current_task = (struct task_struct *)elem;
	return (unsigned long)current_task->cpu;
}

const char *get_thread_name(void *elem)
{
	struct task_struct *current_task = (struct task_struct *)elem;
	return current_task->comm;
}

void print_zone_dm(unsigned long cpu_num,
						  const char *name,
						  unsigned long long count,
						  int percentage)
{
	printk("20191155gwakyounghun thread %s: cpu[%ld] called pxt4_file_write_iter() \
%lld times (%d%%)\n",
		   name, cpu_num, count, percentage);
}
