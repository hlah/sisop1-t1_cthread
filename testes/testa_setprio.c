#include "../include/cthread.h"
#include <stddef.h>
#include <stdio.h>

void* mythread(void*);
void* mythread_low(void*);

int main() {

	int thread1 = ccreate(mythread, (void*)1, 2);
	int thread2 = ccreate(mythread_low, (void*)2, 2);
	int thread3 = ccreate(mythread, (void*)3, 2);

	cyield();

	printf("main: i'm back!!!\n");

	cjoin(thread1);
	cjoin(thread2);
	cjoin(thread3);

	return 0;
}


void* mythread(void* arg) {
	int i=0;
	printf("entering thread %d\n", (int)arg);

	cyield();
	csetprio(0, 0);

	for( i=0; i<5; i++ ) {
		printf("mytrhead %d: hello world (%d)\n", (int)arg, i+1);
		cyield();
	}

	return NULL;
}

void* mythread_low(void* arg) {
	int i=0;
	printf("entering thread %d\n", (int)arg);

	csetprio(0, 1);

	for( i=0; i<5; i++ ) {
		printf("mytrhead %d: hello world (%d)\n", (int)arg, i+1);
		cyield();
	}

	return NULL;
}
