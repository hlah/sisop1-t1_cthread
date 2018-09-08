#include "../include/cthread_internal.h"

int cwait(csem_t *sem) {
    sem->count--;
    
    if (sem->count < 0) { // bloqueia processo
        sem->count++;
        return cthread_sem_block(sem);
    }

    return 0;
}
