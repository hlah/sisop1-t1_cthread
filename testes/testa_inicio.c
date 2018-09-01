#include "../include/cthread.h"
#include <stddef.h>
#include <stdio.h>

void* mythread(void*);

int main() {

	int thread1 = ccreate(mythread, (void*)1, 2);

	int thread2 = ccreate(mythread, (void*)2, 1);


	printf("main: i'm back!!!\n");

	return 0;
}

void* mythread(void* arg) {

	printf("mytrhead: hello world (%d)\n", (int)arg);

	return NULL;
}
