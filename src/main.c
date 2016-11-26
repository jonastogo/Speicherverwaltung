
#include "../include/speicherverwaltung.h"
#include "../include/display.h"
#include <stdio.h>

int main(){
	printf("\n\n");
	struct memblock *p=cm_malloc(1700);
	printf(" Adress: %i \n\n\n\n", p);
	struct memblock *q=cm_malloc(1600);
	printf(" Adress: %i \n\n\n\n", q);
	cm_free(p);
	struct memblock *r=cm_malloc(1000);
	printf(" Adress: %i \n\n\n\n", r);
	struct memblock *t=cm_malloc(2000);
	printf(" Adress: %i \n\n\n\n", t);
	struct memblock *k=cm_malloc(2100);
	printf(" Adress: %i \n\n\n\n", k);
	printf(" Allocation and deallocation is done successfully!\n\n");
	show_absolute();
}
