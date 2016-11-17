/*
 * speicherverwaltung.c
 *
 *  Created on: 16.11.2016
 *      Author: Jonas-Lampe
 */


#include<stdio.h>
#include<stddef.h>
#include "../include/speicherverwaltung.h"

char mempool[MEM_POOL_SIZE];
struct memblock *freeman=(void*)mempool;

void init_heap(void){
 freeman->size=MEM_POOL_SIZE-sizeof(struct memblock);
 freeman->free=MAGIC_INT;
 freeman->next=NULL;
}

void *cm_malloc(size_t size){
	struct memblock *curr,*prev;
	void *result;
	if(!(freeman->size)){
		init_heap();
		printf("Memory initialized\n");
	}
	curr=freeman;
	while((((curr->size)<size)||((curr->free)==0))&&(curr->next!=NULL)){
		prev=curr;
		curr=curr->next;
		printf("One block checked\n");
	}
	if((curr->size)==size){
		curr->free=0;
		result=(void*)(++curr);
		printf("Exact fitting block allocated\n");
		return result;
	}
	else if((curr->size)>(size+sizeof(struct memblock))){
		split(curr,size);
		result=(void*)(++curr);
		printf("Fitting block allocated with a split\n");
		return result;
	}
	else{
		result=NULL;
	  	printf("Sorry. No sufficient memory to allocate\n");
	  	return result;
	}
}

void split(struct memblock *fitting_slot,size_t size){
	struct memblock *new = (void*)((void*)fitting_slot+size+sizeof(struct memblock));
	new->size=(fitting_slot->size)-size-sizeof(struct memblock);
	new->free=MAGIC_INT;
	new->next=fitting_slot->next;
	fitting_slot->size=size;
	fitting_slot->free=0;
	fitting_slot->next=new;
}

void cm_free(void *ptr){
	if(((void*)mempool<=ptr)&&(ptr<=(void*)(mempool + 20000))){
		struct memblock* curr=ptr;
		--curr;
		curr->free=MAGIC_INT;
		merge();
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
