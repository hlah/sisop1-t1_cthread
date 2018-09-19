#include "../include/cthread_internal.h"

#include <stdio.h>

int cwait(csem_t *sem) {
    sem->count--;
    
    if (sem->count < 0) { // bloqueia processo
        sem->count++;
        return cthread_sem_block(sem);
    }

    DEBUG_PRINT("Thread %d entering critical sector...\n", cthread_executing_thread->tid);
    return 0;
}
