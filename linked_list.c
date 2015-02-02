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
void Destroy (){
	free(mem_ptr);
	head = NULL;
	free_ptr = NULL;
} 		 
int Insert (int key,char * value_ptr, int value_len){
	if(head == NULL){
		head = free_ptr;
		free_ptr += block_size;
		head->next = NULL;
		head->key = key;
		head->val_length = value_len;
		head->value = head + 8 + sizeof(head);
		memcpy((void *)head->value,(void *)value_ptr,value_len);
	}
	else{
		struct list_node *prev = free_ptr - block_size;
		free_ptr->next = NULL;
		prev->next = free_ptr;
		free_ptr->key = key;
		free_ptr->val_length = value_len;
		free_ptr->value = free_ptr + 8 + sizeof(head);
		memcpy((void *)free_ptr->value,(void *)value_ptr,value_len);
		free_ptr += block_size;
	}
}
int Delete (int key){
	struct list_node * current = head;
	while(current != NULL){
}
char* Lookup (int key){}
void PrintList (){
	struct list_node * current = head;
	while(current != NULL){
		printf("Key: %i Value: %s \n",current->key,current->value);
		current = current->next;
	}
	printf("\n\n");

}

