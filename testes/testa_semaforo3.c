#include "../include/cthread.h"
#include <stddef.h>
#include <stdio.h>

csem_t sem;

void* mythread1(void*);
void* mythread2(void*);

int main() {

	int thread1;

	csem_init(&sem, 1);
	thread1 = ccreate(mythread1, (void*)1, 1);

	cjoin(thread1);

	printf("Main: i'm back!\n");

	return 0;
}


void* mythread1(void* arg) {
	int i=0;
	int thread2;
	printf("Hello from thread %d\n", (int)(arg));

	cwait(&sem);
	printf("Thread %d inside critical sector\n", (int)(arg));
	printf("Thread %d creating new thread\n", (int)(arg));
	thread2 = ccreate(mythread2, (void*)2, 0);
	cyield();
	printf("Thread %d lefting critical sector\n", (int)(arg));
	csignal(&sem);

	for( i=0; i<3; i++ ) {
		cwait(&sem);
		printf("Thread %d inside critical sector\n", (int)(arg));
		cyield();
		printf("Thread %d lefting critical sector\n", (int)(arg));
		csignal(&sem);
	}

	cjoin(thread2);

	printf("Thread %d ending\n", (int)(arg));

	return NULL;
}

void* mythread2(void* arg) {
	int i=0;
	printf("Hello from thread %d\n", (int)(arg));

	for( i=0; i<3; i++ ) {
		cwait(&sem);
		printf("Thread %d inside critical sector\n", (int)(arg));
		cyield();
		printf("Thread %d lefting critical sector\n", (int)(arg));
		csignal(&sem);
	}
	printf("Thread %d ending\n", (int)(arg));

	return NULL;
}

