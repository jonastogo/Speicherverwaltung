
#ifndef INCLUDE_SPEICHERVERWALTUNG_H_
#define INCLUDE_SPEICHERVERWALTUNG_H_

#include <stdio.h>
#include <stddef.h>

#define MEM_POOL_SIZE 16384
/*0xacdcacdcUL*/

#define MAGIC_INT 2900143324UL

/*unsigned long MAGIC_INT = 2900143324UL;*/


typedef unsigned char byte;

typedef struct memblock{
	size_t size;
	struct memblock *next;
}memblock_t;

void init_heap();
void split(struct memblock *fitting_slot, size_t size);
void *cm_malloc(size_t size);
void *cm_malloc_split(size_t size);
void merge();
void cm_free(void *ptr);
int *absolute(void);

#endif /* INCLUDE_SPEICHERVERWALTUNG_H_ */
