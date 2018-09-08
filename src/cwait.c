#include "../include/cthread_internal.h"

int cwait(csem_t *sem) {
    // cthread_spin_lock();

    sem->count--;
    if (sem->count < 0) { // bloqueia processo
        // cthread_spin_unlock();
        sem->count++;
        return cthread_sem_block(sem);
    }

    // cthread_spin_unlock();
    return 0;

}
