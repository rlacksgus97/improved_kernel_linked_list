#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <linux/time.h>

struct my_list_head {
	struct my_list_head *next_i, *prev_i, *next_n, *prev_n;
};

#define list_entry(ptr, type, member) \
	container_of(ptr, type, member)

#define list_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); pos = pos->next)
	
#define list_first_entry_left(ptr, type, member) \
	list_entry((ptr)->prev_n, type, member)
	
#define list_first_entry_right(ptr, type, member) \
	list_entry((ptr)->next_n, type, member)
	
#define list_next_entry(pos, member) \
	list_entry((pos)->member.next_n, typeof(*(pos)), member)
	
#define list_prev_entry(pos, member) \
	list_entry((pos)->member.prev_n, typeof(*(pos)), member)
	
#define list_for_each_entry_left(pos, head, member)				\
	for (pos = list_first_entry_left(head, typeof(*pos), member);	\
	     &pos->member != NULL;					\
	     pos = list_prev_entry(pos, member))
	    
#define list_for_each_entry_right(pos, head, member)				\
	for (pos = list_first_entry_right(head, typeof(*pos), member);	\
	     &pos->member != NULL;					\
	     pos = list_next_entry(pos, member))

//improved version
struct my_list {
	int num;
	struct my_list_head list;
};

static inline void INIT_MY_LIST_HEAD(struct my_list_head *list)
{
	list->next_i = list;
	list->prev_i = list;
	list->next_n = list;
	list->prev_n = list;
}

static inline void list_insert_by_value(struct my_list *pos, struct my_list_head *head, int value, int new_value) {
	struct my_list *new_node = kmalloc(sizeof(struct my_list), GFP_KERNEL);
	new_node->num = new_value;
	struct my_list_head *new = &(new_node->list);
	
	if (new_value%2 == 1 && head->prev_n==head) {
		head->prev_n = new;
		new->next_n = head;
		return 0;
	}
	if (new_value%2 == 0 && head->next_n==head){
		head->next_n = new;
		new->prev_n = head;
		return 0;
	}
	
	if (value%2 == 1) {
		list_for_each_entry_left(pos, head, list){
			if (pos->num == value) {
				//just put in
				if(new_value%2==1){
					head->prev_n->next_n = new;
					new->prev_n = head->prev_n;
					
					head->prev_n = new;
					new->next_n = head;
				}
				
				if(new_value%2==0){
					head->next_n->prev_n = new;
					new->next_n = head->next_n;
					
					head->next_n = new;
					new->prev_n = head;
				
				}
				
				//bind pos_node and new_node for real index
				struct my_list_head *pos_original_next = pos->list.next_i;
				pos->list.next_i = new;
				new->prev_i = &(pos->list);
				
				new->next_i = pos_original_next;
				if (pos_original_next != NULL){
					pos_original_next->prev_i = new;
				}
				
				break;
			}
		}
	}
	else {
		list_for_each_entry_right(pos, head, list){
			if (pos->num == value) {
				//just put in
				if(new_value%2==1){
					head->prev_n->next_n = new;
					new->prev_n = head->prev_n;
					
					head->prev_n = new;
					new->next_n = head;
				}
				
				if(new_value%2==0){
					head->next_n->prev_n = new;
					new->next_n = head->next_n;
					
					head->next_n = new;
					new->prev_n = head;
				
				}
				
				//bind pos_node and new_node for real index
				struct my_list_head *pos_original_next = pos->list.next_i;
				pos->list.next_i = new;
				new->prev_i = &(pos->list);
				
				new->next_i = pos_original_next;
				if (pos_original_next != NULL){
					pos_original_next->prev_i = new;
				}
				
				break;
			}
		}
	}
}

static inline void list_delete_by_value(struct my_list *pos, struct my_list_head *head, int value) {
	struct my_list *new_node = kmalloc(sizeof(struct my_list), GFP_KERNEL);
	new_node->num = new_value;
	struct my_list_head *new = &(new_node->list);
	
	if (new_value%2 == 1 && head->prev_n==head) {
		head->prev_n = new;
		new->next_n = head;
		return 0;
	}
	if (new_value%2 == 0 && head->next_n==head){
		head->next_n = new;
		new->prev_n = head;
		return 0;
	}
	
	if (value%2 == 1) {
		list_for_each_entry_left(pos, head, list){
			if (pos->num == value) {
				//just put in
				if(new_value%2==1){
					head->prev_n->next_n = new;
					new->prev_n = head->prev_n;
					
					head->prev_n = new;
					new->next_n = head;
				}
				
				if(new_value%2==0){
					head->next_n->prev_n = new;
					new->next_n = head->next_n;
					
					head->next_n = new;
					new->prev_n = head;
				
				}
				
				//bind pos_node and new_node for real index
				struct my_list_head *pos_original_next = pos->list.next_i;
				pos->list.next_i = new;
				new->prev_i = &(pos->list);
				
				new->next_i = pos_original_next;
				if (pos_original_next != NULL){
					pos_original_next->prev_i = new;
				}
				
				break;
			}
		}
	}
	else {
		list_for_each_entry_right(pos, head, list){
			if (pos->num == value) {
				//just put in
				if(new_value%2==1){
					head->prev_n->next_n = new;
					new->prev_n = head->prev_n;
					
					head->prev_n = new;
					new->next_n = head;
				}
				
				if(new_value%2==0){
					head->next_n->prev_n = new;
					new->next_n = head->next_n;
					
					head->next_n = new;
					new->prev_n = head;
				
				}
				
				//bind pos_node and new_node for real index
				struct my_list_head *pos_original_next = pos->list.next_i;
				pos->list.next_i = new;
				new->prev_i = &(pos->list);
				
				new->next_i = pos_original_next;
				if (pos_original_next != NULL){
					pos_original_next->prev_i = new;
				}
				
				break;
			}
		}
	}
}

void test(void){
	
	ktime_t start, end;
	s64 time_new, time_original;
	//start=ktime_get();
	//end=ktime_get();
	//time_new=ktime_to_ns(ktime_sub(end, start));
	//printk("New Insert : %lld ns\n", (long long)time_new);
	//printk("Original Insert : %lld ns\n", (long long)time_original);
	
	struct my_list_head head;
	struct my_list *mylist;
	INIT_MY_LIST_HEAD(&head);
	
	start=ktime_get();
	int i = 0;
	for (i=2; i<10000; i++){
		list_insert_by_value(mylist, &head, i, i+1);
		//printk("step %d\n", i);	
	}
	end=ktime_get();
	time_new=ktime_to_ns(ktime_sub(end, start));
	printk("New Insert : %lld ns\n", (long long)time_new);
	
	
	

}

int __init project_module_init(void)
{
	printk("Hello Module!\n");
	test();
	return 0;
}

void __exit project_module_cleanup(void)
{
	printk("Bye Module!\n");
}

module_init(project_module_init);
module_exit(project_module_cleanup);
MODULE_LICENSE("GPL");

/*#define search_by_value_odd_even(pos, head, member, value, num_name) (\
	if (value%2 == 0) {, \
		(pos, head, member) {, \
				return *pos->member, \
			}, \
		}, \
	else {, \
		list_for_each_entry_right(pos, head, member) {, \
			if(pos->name == value) {, \
				return *pos->member, \
			}, \
		}, \
	), \
	*/





