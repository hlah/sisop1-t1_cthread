#include "../include/cthread.h"
#include <stddef.h>
#include <stdio.h>

void* mythread(void*);

int main() {

	int thread1 = ccreate(mythread, (void*)1, 2);
	int thread2 = ccreate(mythread, (void*)2, 2);
	int thread3 = ccreate(mythread, (void*)3, 1);


	printf("main: i'm back!!!\n");

	return 0;
}

void* mythread(void* arg) {
	int i=0;

	for( i=0; i<5; i++ ) {
		printf("mytrhead %d: hello world (%d)\n", (int)arg, i+1);
		cyield();
	}

	return NULL;
}
