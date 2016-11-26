
#ifndef INCLUDE_SPEICHERVERWALTUNG_H_
#define INCLUDE_SPEICHERVERWALTUNG_H_

#include <stdio.h>
#include <stddef.h>

#define MEM_POOL_SIZE 16384
#define MAGIC_INT 0xacdcacdc


typedef unsigned char byte;

struct memblock{
	size_t size;
	struct memblock *next;
}memblock;


void init_heap();
void split(struct memblock *fitting_slot, size_t size);
struct memblock *cm_malloc(size_t size);
void merge();
void cm_free(struct memblock *ptr);

#endif /* INCLUDE_SPEICHERVERWALTUNG_H_ */
