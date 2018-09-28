#include "../include/cthread.h"
#include <stddef.h>
#include <stdio.h>

csem_t sem;

void* mythread(void*);

int main() {

	int thread1;
	int thread2;

	csem_init(&sem, 1);
	thread1 = ccreate(mythread, (void*)1, 1);
	thread2 = ccreate(mythread, (void*)2, 0);

	cjoin(thread1);
	cjoin(thread2);

	printf("Main: i'm back!\n");

	return 0;
}


void* mythread(void* arg) {
	printf("Hello from thread %d\n", (int)(arg));

	cwait(&sem);
	printf("Thread %d inside critical sector\n", (int)(arg));
	cyield();
	printf("Thread %d still inside critical sector\n", (int)(arg));
	csignal(&sem);

	printf("Thread %d ending\n", (int)(arg));

	return NULL;
}

