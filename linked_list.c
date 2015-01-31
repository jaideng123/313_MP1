#include "linked_list.h"

void Init (int M, int b){
	//TODO error checking(i.e. b < 12)
	block_size = b;
	max_blocks = M/b;
	free_ptr = (struct list_node *) malloc(M);
	head = 0;
} 
void Destroy (){} 		 
int Insert (int key,char * value_ptr, int value_len){
	if(head == 0){
		head = free_ptr;
		free_ptr += block_size;
		head->next = 0;
		head->key = key;
		head->val_length = value_len;
		memcpy(head->value,value_ptr,value_len);
	}
	else{
		struct list_node *prev = free_ptr - block_size;
		free_ptr->next = 0;
		prev->next = free_ptr;
		free_ptr->key = key;
		free_ptr->val_length = value_len;
		memcpy(free_ptr->value,value_ptr,value_len);
		free_ptr += block_size;
	}
}
int Delete (int key){}
char* Lookup (int key){}
void PrintList (){}

