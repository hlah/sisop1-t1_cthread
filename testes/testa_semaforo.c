#include "../include/cthread.h"
#include <stddef.h>
#include <stdio.h>

csem_t sem;

void* mythread(void*);

int main() {

	int thread1;
	int thread2;
	int thread3;
	int thread4;
	int thread5;
	int thread6;

	csem_init(&sem, 1);
	thread1 = ccreate(mythread, (void*)1, 2);
	thread2 = ccreate(mythread, (void*)2, 0);
	thread3 = ccreate(mythread, (void*)3, 2);
	thread4 = ccreate(mythread, (void*)4, 0);
	thread5 = ccreate(mythread, (void*)5, 2);
	thread6 = ccreate(mythread, (void*)6, 0);

	cjoin(thread1);
	cjoin(thread2);
	cjoin(thread3);
	cjoin(thread4);
	cjoin(thread5);
	cjoin(thread6);

	printf("Main: i'm back!\n");

	return 0;
}


void* mythread(void* arg) {
	printf("Hello from thread %d\n", (int)(arg));

	cyield();

	cwait(&sem);
	printf("Thread %d inside critical sector\n", (int)(arg));
	cyield();
	printf("Thread %d still inside critical sector\n", (int)(arg));
	csignal(&sem);
	printf("Thread %d ending\n", (int)(arg));

	return NULL;
}

