#include "linked_list2.h"
#include <stdio.h>
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
			free_list[t] = ((struct list_node *)mem_ptr)+b*i;
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
	if(num_blocks == max_blocks){
		printf("\nError: linked list is full\n");
		return EXIT_FAILURE;
	}
	if(value_len > block_size-(8 + sizeof(head))){
		printf("\nError: value is too long\n");
		return EXIT_FAILURE;
	}
	if(head == NULL){
		head = free_ptr;
		free_ptr += block_size;
		head->next = NULL;
		head->key = key;
		head->val_length = value_len;
		//8 = sizeof key + val_length
		head->value = head + 8 + sizeof(head);
		memcpy((void *)head->value,(void *)value_ptr,value_len);
	}
	else{
		struct list_node *prev = free_ptr - block_size;
		free_ptr->next = NULL;
		prev->next = free_ptr;
		free_ptr->key = key;
		free_ptr->val_length = value_len;
		//8 = sizeof key + val_length
		free_ptr->value = free_ptr + 8 + sizeof(head);
		memcpy((void *)free_ptr->value,(void *)value_ptr,value_len);
		free_ptr += block_size;
	}
	num_blocks++;
	return EXIT_SUCCESS;
}
//deletes node with certain key
int Delete (int key){
	struct list_node * current = head;
	struct list_node * prev = NULL;
	while(current != NULL && current->key != key){
		prev = current;
		current = current->next;
	}
	if(current != NULL){
		if(prev != NULL)
			prev->next = current->next;
		else
			head = current->next;
		return EXIT_SUCCESS;
	}
	else{
		printf("\nError: Key not found\n");
		return EXIT_FAILURE;
	}
}
//return pointer to matching key value
char* Lookup (int key){
	struct list_node * current = head;
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
	struct list_node * current = head;
	while(current != NULL){
		if(current->val_length == sizeof(int))
			printf("Key: %i Value: %u \n",current->key,*(int*)current->value);
		else
			printf("Key: %i Value: %s \n",current->key,current->value);
		current = current->next;
	}
	printf("\n\n");

}