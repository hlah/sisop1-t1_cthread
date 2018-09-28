#include "../include/cthread_internal.h"

#include <stdio.h>

int cwait(csem_t *sem) {
    sem->count--;

	if(sem->count < 0) {
		AppendFila2(sem->fila, (void*)cthread_executing_thread);
		DEBUG_PRINT("Thread %d blocked (tried to access unavailable resource)\n", cthread_executing_thread->tid);
		cthread_schedule(cthread_executing_thread, 1);
	}
    
	/*
    if (sem->count < 0) { // bloqueia processo
        sem->count++;
        return cthread_sem_block(sem);
    }
	*/

    DEBUG_PRINT("Thread %d entering critical sector...\n", cthread_executing_thread->tid);
    return 0;
}
