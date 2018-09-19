#include "../include/cthread_internal.h"

#include <stdio.h>

int cthread_sem_wakeup(csem_t* sem, PFILA2 fifoPrio){

    TCB_t* unblocked_thread = GetAtIteratorFila2(fifoPrio);

    sem->count--;
    unblocked_thread->state = CTHREAD_STATE_APTO;
    AppendFila2(&cthread_priority_fifos[unblocked_thread->prio], (void*) unblocked_thread);
    DeleteAtIteratorFila2(fifoPrio);
    DEBUG_PRINT("Thread %d unblocked (resource available)\n", unblocked_thread->tid);

    if (unblocked_thread->prio > cthread_executing_thread->prio) // checa prioridade do processo bloqueado
        return cthread_schedule(cthread_executing_thread, 0);

    return 0;
}
