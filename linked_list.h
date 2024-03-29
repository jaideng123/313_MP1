#ifndef _linked_list_h_                   // include file only once
#define _linked_list_h_
#include <stdint.h>
#define NULL 0
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

int max_blocks;
int block_size;
int current_size;
int num_blocks;
void* mem_ptr;

struct list_node *head;
struct list_node *free_ptr;

struct list_node{
	struct list_node *next;
	uint32_t key;
	uint32_t val_length;
	void* value;
};

void 	Init (int M, int b); // initializes the linked list, should be called once from the main
void 	Destroy (); 		 //	destroys the linked list and cleans resources
int 	Insert (int key,char * value_ptr, int value_len); // inserts the key and copies the value to the payload
int 	Delete (int key); 	 // delete the whole block containing that particular key. When multiple entries with the same key, delete only the first one	
char* 	Lookup (int key);	 //	Looks up the first item with the given and returns a pointer to the value portion (the value length and the actual value) 
							//(the user can read or modify after obtaining the pointer)
void 	PrintList ();		// prints the entire list by following the next pointers. Print the keys and the length	of the value
#endif 
