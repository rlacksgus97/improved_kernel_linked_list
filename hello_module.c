#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <linux/time.h>

struct my_node {
	struct list_head list;
	int data;
};

struct list_head my_list;
struct my_node *current_node;

void original(void)
{
	ktime_t start, end;
	s64 time_i, time_s, time_d;
	INIT_LIST_HEAD(&my_list);
	
	start=ktime_get();
	struct my_node *temp = kmalloc(sizeof(struct my_node), GFP_KERNEL);
	temp->data = 1;
	list_add(&temp->list, &my_list);
	int j;
	for (j=2; j<100000; j++){
		struct my_node *new = kmalloc(sizeof(struct my_node), GFP_KERNEL);
		new->data = j;
		list_for_each_entry(current_node, &my_list, list){
			if (current_node->data == j-1) {
				list_add(&new->list, &my_list);
				break;
			}
		}
	}
	end=ktime_get();
	time_i=ktime_to_ns(ktime_sub(end, start));
	printk("Original Insert : %lld ns\n", (long long)time_i);
	
	
	start=ktime_get();
	struct my_node *current_node = kmalloc(sizeof(struct my_node), GFP_KERNEL);
	list_for_each_entry(current_node, &my_list, list){
		if (current_node->data == 50000){
			printk("search value: %d\n", current_node->data);
		}
	}
	end=ktime_get();
	time_s=ktime_to_ns(ktime_sub(end, start));
	printk("Original Search : %lld ns\n", (long long)time_s);
	
	start=ktime_get();
	struct my_node *tmp;
	for (j=2; j<100000; j++){
		list_for_each_entry_safe(current_node, tmp, &my_list, list){
			if (current_node->data == j){
				list_del(&current_node->list);
				kfree(current_node);
				break;
			}
		}
	}
	end=ktime_get();
	time_s=ktime_to_ns(ktime_sub(end, start));
	printk("Original Delete : %lld ns\n", (long long)time_s);
	
}

int __init project_module_init(void)
{
	printk("Hello Module!\n");
	original();
	return 0;
}

void __exit project_module_cleanup(void)
{
	printk("Bye Module!\n");
}

module_init(project_module_init);
module_exit(project_module_cleanup);
MODULE_LICENSE("GPL");
	
