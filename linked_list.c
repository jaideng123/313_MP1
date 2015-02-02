#include "linked_list.h"
#include <stdio.h>
void Init (int M, int b){
	//TODO error checking(i.e. b < 12)
	block_size = b;
	max_blocks = M/b;
	mem_ptr = malloc(M);
	free_ptr = (struct list_node *) mem_ptr;
	head = NULL;
} 
//reset pointers, free mem
void Destroy (){
	free(mem_ptr);
	head = NULL;
	free_ptr = NULL;
} 		
//insert new node at end 
int Insert (int key,char * value_ptr, int value_len){
	//TODO error checking(mem is full)
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
}
//deletes node with certain key
//return 1 if successful, 0 otherwise
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
		return 1;
	}
	else
		return 0;
}
//return pointer to matching key value
char* Lookup (int key){
	struct list_node * current = head;
	while(current != NULL && current->key != key)
		current = current->next;
	if(current != NULL){
		return current->value;
	}
	else
		return NULL;
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

