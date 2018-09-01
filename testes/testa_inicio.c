#include "../include/cthread.h"
#include <stddef.h>
#include <stdio.h>

void* mythread(void*);

int main() {

	int thread = ccreate(mythread, NULL, 2);



	return 0;
}

void* mythread(void* arg) {

	printf("mytrhead: hello world\n");

	return NULL;
}
