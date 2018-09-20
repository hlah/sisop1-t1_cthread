#include "../include/cthread.h"
#include <stddef.h>
#include <stdio.h>

csem_t sem;

void* mythread(void*);

int main() {

	int thread1;
	int thread2;

	csem_init(&sem, 1);
	thread1 = ccreate(mythread, (void*)1, CTHREAD_MID_PRIORITY);
	thread2 = ccreate(mythread, (void*)2, CTHREAD_HIG_PRIORITY);

	printf("Main: i'm back!\n");

	return 0;
}


void* mythread(void* arg) {

	cwait(&sem);
	printf("Thread %d inside critical sector", int(arg));
	cyield();
	printf("Thread %d still inside critical sector", int(arg));
	csignal(&sem);

	printf("Thread %d ending", int(arg));

	return NULL;
}

