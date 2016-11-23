/*
 * speicherverwaltung.c
 *
 *  Created on: 16.11.2016
 *      Author: Jonas-Lampe
 */


#include <stdio.h>
#include <stddef.h>
#include "../include/speicherverwaltung.h"

char mempool[MEM_POOL_SIZE];
struct memblock *freeman=(void*)mempool;

void init_heap(void){
	printf("Mempool: %i", (void*)mempool);
	freeman->size=MEM_POOL_SIZE-sizeof(struct memblock);
	freeman->free=MAGIC_INT;
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
	printf("%zu -> ", first->size);
	while(first->next!=NULL){
		first = first->next;
		printf("%zu -> ", first->size);
	}
	printf("Memory initialized\n\n");
}

void *cm_malloc(size_t size){
	struct memblock *curr,*prev = NULL, *list;
	void *result;
	if(!(freeman->size)){
		init_heap();
	}
	list = freeman;
	printf("%zu -> ", list->size);
	while(list->next!=NULL){
		list = list->next;
		printf("%zu -> ", list->size);
	}
	printf("\n");
	printf("%zu\n", size);
	curr=freeman;
	while(curr->size<size && curr->next!=NULL){
		prev=curr;
		curr=curr->next;
		printf(" %zu <-> %zu\n", size, curr->size);
		printf(" One block checked\n");
	}
	if((curr->size)>=size){
		if(prev == NULL){
			printf("prev == NULL\n");
			freeman = curr->next;
		}
		else{
			printf("prev != NULL\n");
			prev->next = curr->next;
		}
		result=(void*)(++curr);
		printf(" Exact fitting block allocated\n\n");
		return result;
	}
	else{
		result=NULL;
	  	printf(" Sorry. No sufficient memory to allocate\n\n");
	  	return result;
	}
}


void split(struct memblock *fitting_slot,size_t size){
	struct memblock *new = (void*)((void*)fitting_slot+size+sizeof(struct memblock));
	new->size=(fitting_slot->size)-size-sizeof(struct memblock);
	new->free=MAGIC_INT;
	new->next=fitting_slot->next;
	fitting_slot->size=size;
	fitting_slot->free=MAGIC_INT;
	fitting_slot->next=new;
}

void cm_free(void *ptr){
	struct memblock *list = freeman;
	printf("%i <= %i\n", (void*)mempool, ptr);
	printf("%i\n", mempool);
	ptr = ((char*)mempool) + ptr;
	if((void*)mempool<=ptr && ptr<=(void*)(mempool + 16384)){
		struct memblock *curr=ptr;
		--curr;
		curr->free=MAGIC_INT;
		while(!list->next){
			list = list->next;
		}
		list->next = curr;
		printf("Memoryarea was cleared!\n");
	}
	else {
		printf("Please provide a valid pointer allocated by cm_malloc\n");
	}
}

void merge(){
	struct memblock *curr,*prev;
	curr=freeman;
	while((curr->next)!=NULL){
		if((curr->free) && (curr->next->free)){
			curr->size+=(curr->next->size)+sizeof(struct memblock);
			curr->next=curr->next->next;
		}
		prev=curr;
		curr=curr->next;
	}
}
