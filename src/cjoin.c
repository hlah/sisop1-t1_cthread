#include "../include/cthread_internal.h"
#include <stdio.h>

int cjoin(int tid) {

	// acha thread
	TCB_t* thread = cthread_find_thread(tid);
	if( thread == NULL ) {
		return -1;
	}

	// verifica se já há outra esperando
	if( thread->data != NULL ) {
		return -1;
	}

	// bloqueia thread
	DEBUG_PRINT("thread %d waiting for thread %d\n", cthread_executing_thread->tid, tid);
	cthread_executing_thread->state = CTHREAD_STATE_BLOCK;
	thread->data = (void*) cthread_executing_thread;
	cthread_schedule(cthread_executing_thread, 1);

	return 0;
}
