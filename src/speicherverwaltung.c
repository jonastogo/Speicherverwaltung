/*
 * speicherverwaltung.c
 *
 *  Created on: 16.11.2016
 *      Author: Jonas-Lampe, Alexander-Sochart
 */


#include <stdio.h>
#include <stddef.h>
#include "../include/speicherverwaltung.h"

char mempool[MEM_POOL_SIZE];
struct memblock *freeman=(void*)mempool;

void init_heap(void){
	printf(" Mempool: %i\n", (void*)mempool);
	printf(" Mempool PAddr: %i\n", &mempool);
	freeman->size=MEM_POOL_SIZE-sizeof(struct memblock);
	freeman->next=NULL;
	struct memblock *curr = freeman;
	struct memblock *first;
	split(curr, 1600);
	first = curr;
	curr = curr->next;
	split(curr, 1500);
	curr = curr->next;
	split(curr, 1400);
	curr = curr->next;
	split(curr, 1700);
	curr = curr->next;
	split(curr, 1700);
	curr = curr->next;
	split(curr, 1800);
	curr = curr->next;
	split(curr, 2000);
	curr = curr->next;
	split(curr, 1700);
	curr = curr->next;
	split(curr, 1400);
	curr = curr->next;
	freeman = first;
	printf(" %zu -> ", first->size);
	while(first->next!=NULL){
		first = first->next;
		printf("%zu -> ", first->size);
	}
	printf("\n Memory initialized\n\n\n\n");
}

void *cm_malloc(size_t size){
	struct memblock *curr,*prev = NULL, *list;
	void *result;
	if(!(freeman->size)){
		init_heap();
	}
	list = freeman;
	printf("TO DO: %zu\n", size);
	printf(" %zu -> ", list->size);
	while(list->next!=NULL){
		list = list->next;
		printf(" %zu -> ", list->size);
	}
	printf("\n");
	printf(" CHECK BLOCKS!\n");
	curr=freeman;
	while(curr->size<size && curr->next!=NULL){
		prev=curr;
		printf(" %zu <-> %zu  -> ", size, curr->size);
		printf(" block checked\n");
		curr=curr->next;
	}
	printf(" %zu <-> %zu  -> ", size, curr->size);
	printf(" block checked\n");
	if((curr->size)>=size){
		if(prev == NULL){
			freeman = curr->next;
		}
		else{
			prev->next = curr->next;
		}
		curr->next=MAGIC_INT;
		result=(void*)++curr;
		printf(" Fitting block allocated on: ");
		return result;
	}
	else{
		result=NULL;
	  	printf(" Sorry. No sufficient memory to allocate on: ");
	  	return result;
	}
}

void *cm_malloc_split(size_t size){
	struct memblock *curr,*prev;
	void *result;
	if(!(freeman->size)){
		init_heap();
	}
	curr=freeman;
	while(curr->size<size && curr->next!=NULL){
		prev=curr;
		curr=curr->next;
		printf(" block checked\n");
	}
	if((curr->size)==size){
		curr->next=MAGIC_INT;
		result=(void*)++curr;
		printf(" Exact fitting block allocated on: ");
		return result;
	}
	else if((curr->size)>(size+2*sizeof(struct memblock)+32*sizeof(byte))){
		split(curr,size);
		curr->next=MAGIC_INT;
		result=(void*)++curr;
		printf(" Fitting block allocated with a split on: ");
		return result;
	}
	else{
		result=NULL;
		printf(" Sorry. No sufficient memory to allocate on: ");
		return result;
	}
}


void split(struct memblock *fitting_slot,size_t size){
	struct memblock *new = (void*)((void*)fitting_slot+size+sizeof(struct memblock));
	new->size=(fitting_slot->size)-size-sizeof(struct memblock);
	new->next=fitting_slot->next;
	fitting_slot->size=size;
	fitting_slot->next=new;
}

void cm_free(void *ptr){
	printf("FREEING \n");
	struct memblock *first = freeman;
	if(((void*)mempool<=ptr)&&(ptr<=(void*)(mempool+16384))){
		struct memblock* curr=ptr;
		--curr;
		curr->next=first;
		freeman = curr;
	}
	else
		printf("Please provide a valid pointer allocated by MyMalloc\n");
}

int *absolute(void){
	unsigned long *mempoolAddr = &mempool;
	int i;
	unsigned int *full = (unsigned int*) malloc(sizeof(unsigned int)*10);
	for(i = 0; i<10; i++){
		memblock_t *start = mempoolAddr;

		if(start->next == MAGIC_INT){
			full[i] = 1;
		}
		else {
			full[i] = 0;
		}

		unsigned long pointer = mempoolAddr;
		unsigned long pointer_all = pointer + sizeof(memblock_t) + start->size;
		mempoolAddr = pointer_all;
	}
	return full;
}

