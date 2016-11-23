
#include "../include/speicherverwaltung.h"
#include <stdio.h>

int main(){
	printf("\n\n");
	char *p=(char)cm_malloc(1700*sizeof(char));
	printf("Adress: %i \n", p);
	char *q=(char)cm_malloc(1600*sizeof(char));
	printf("Adress: %i \n", q);
	char *r=(char)cm_malloc(1000*sizeof(char));
	printf("Adress: %i \n", r);
	char *t=(char)cm_malloc(2000*sizeof(char));
	printf("Adress: %i \n", t);
	char *k=(char)cm_malloc(2100*sizeof(char));
	printf("Adress: %i \n", k);
	cm_free(r);
	printf("Allocation and deallocation is done successfully!");

}
