#define DEBUG
#include "../include/cthread.h"
#include <stddef.h>
#include <stdio.h>

void* mythread(void*);
void* mythread_low(void*);

int main() {

	int thread1 = ccreate(mythread, (void*)1, 2);
	int thread2 = ccreate(mythread, (void*)2, 0);

	cjoin(thread1);
	cjoin(thread2);

	printf("I'm back!\n");

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

void* mythread_low(void* arg) {
	int i=0;

	csetprio(0, 0);

	for( i=0; i<5; i++ ) {
		printf("mytrhead %d: hello world (%d)\n", (int)arg, i+1);
		cyield();
	}

	return NULL;
}
