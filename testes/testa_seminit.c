#include "../include/cthread.h"
#include <stddef.h>
#include <stdio.h>

csem_t sem;

void* mythread(void*);

int main() {

	csem_init(&sem, 1);

	printf("Main: i'm back!\n");

	return 0;
}


