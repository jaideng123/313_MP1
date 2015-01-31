#include "linked_list.h"

void Init (int M, int b){
	//TODO error checking(i.e. b < 12)
	block_size = b;
	max_blocks = M/b;
	free_ptr = (struct list_node *) malloc(M);
} 
void Destroy (){} 		 
int Insert (int key,char * value_ptr, int value_len){}
int Delete (int key){}
char* Lookup (int key){}
void PrintList (){}

