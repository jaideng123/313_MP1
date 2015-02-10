#include "linked_list2.h"
#include <stdio.h>
#define INT_MAX 2147483647
void Init (int M, int b, int t){
	if(b > (8 + sizeof(struct list_node *)) && !(M/t < b)){
		block_size = b;
		max_blocks = (M/b)/t;
		num_blocks = malloc(t*sizeof(int));
		num_lists = t;
		mem_ptr = malloc(M);
		
		head_list = malloc(t*sizeof(struct list_node *));
		for(int i = 0; i < t;++i)
			head_list[i] = NULL;

		free_list = malloc(t*sizeof(struct list_node *));
		for(int i = 0; i < t;++i)
			free_list[i] = ((struct list_node *)mem_ptr)+(max_blocks*block_size*i);
	}
	else{
		printf("\nError: sizes are not valid\n");
	}
} 
//reset pointers, free mem
void Destroy (){
	if(mem_ptr != NULL){
		free(mem_ptr);
		for(int i = 0; i < num_lists;++i){
			head_list[i] = NULL;
			free_list[i] = NULL;
		}
		mem_ptr = NULL;
		free(head_list);
		free(free_list);
		free(num_blocks);
	}
	else
		printf("\nError: nothing to Destroy\n");
} 		
//insert new node at end
int Insert (int key,char * value_ptr, int value_len){
	int index = key/(INT_MAX/num_lists);
	if(num_blocks[index] == max_blocks){
		printf("\nError: linked list is full\n");
		return EXIT_FAILURE;
	}
	if(value_len > block_size-(8 + sizeof(struct list_node *))){
		printf("\nError: value is too long\n");
		return EXIT_FAILURE;
	}
	if(head_list[index] == NULL){
		head_list[index] = free_list[index];
		free_list[index] += block_size;
		head_list[index]->next = NULL;
		head_list[index]->key = key;
		head_list[index]->val_length = value_len;
		//8 = sizeof key + val_length
		head_list[index]->value = head_list[index] + 8 + sizeof(struct list_node *);
		memcpy((void *)head_list[index]->value,(void *)value_ptr,value_len);
	}
	else{
		struct list_node *prev = free_list[index] - block_size;
		free_list[index]->next = NULL;
		prev->next = free_list[index];
		free_list[index]->key = key;
		free_list[index]->val_length = value_len;
		//8 = sizeof key + val_length
		free_list[index]->value = free_list[index] + 8 + sizeof(struct list_node *);
		memcpy((void *)free_list[index]->value,(void *)value_ptr,value_len);
		free_list[index] += block_size;
	}
	num_blocks[index]++;
	return EXIT_SUCCESS;
}
//deletes node with certain key
int Delete (int key){
	int index = key/(INT_MAX/num_lists);
	struct list_node * current = head_list[index];
	struct list_node * prev = NULL;
	while(current != NULL && current->key != key){
		prev = current;
		current = current->next;
	}
	if(current != NULL){
		if(prev != NULL)
			prev->next = current->next;
		else
			head_list[index] = current->next;
		return EXIT_SUCCESS;
	}
	else{
		printf("\nError: Key not found\n");
		return EXIT_FAILURE;
	}
}
//return pointer to matching key value
char* Lookup (int key){
	int index = key/(INT_MAX/num_lists);
	struct list_node * current = head_list[index];
	while(current != NULL && current->key != key)
		current = current->next;
	if(current != NULL){
		return current->value;
	}
	else{
		printf("\nError: Key not found\n");
		return NULL;
	}
}
//prints list in order
void PrintList (){
	for(int i = 0; i < num_lists; ++i){
		printf("List %i:\n",i);
		struct list_node * current = head_list[i];
		while(current != NULL){
			if(current->val_length == sizeof(int))
				printf("Key: %i Value: %u \n",current->key,*(int*)current->value);
			else
				printf("Key: %i Value: %s \n",current->key,current->value);
			current = current->next;
		}
		printf("\n\n");
	}

}