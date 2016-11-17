/*
 * main.c
 *
 *  Created on: 16.11.2016
 *      Author: Jonas-Lampe
 */

#include "../include/speicherverwaltung.h"
#include <stdio.h>

int main(){

 int *p=(int)cm_malloc(100*sizeof(int));
 char *q=(char)cm_malloc(250*sizeof(char));
 int *r=(int)cm_malloc(1000*sizeof(int));
 cm_free(p);
 char *w=(char)cm_malloc(700);
 cm_free(r);
 int *k=(int)cm_malloc(500*sizeof(int));
 printf("Allocation and deallocation is done successfully!");

}
