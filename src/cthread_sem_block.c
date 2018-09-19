#include "../include/cthread_internal.h"

#include <stdio.h>

int cthread_sem_block(csem_t* sem){
    int prio = cthread_executing_thread->prio;
    FirstFila2(sem->fila);

    while (prio > 0){ // procura fila de prioridade correspondente
        NextFila2(sem->fila);
        prio--;
    }

    cthread_executing_thread->state = CTHREAD_STATE_BLOCK;
    AppendFila2(GetAtIteratorFila2(sem->fila) , (void*) cthread_executing_thread); // coloca thread na lista de bloqueados
    DEBUG_PRINT("Thread %d blocked (tried to access unavailable resource)\n", cthread_executing_thread->tid);
    return cthread_schedule(cthread_executing_thread, 1); // escalona proximo thread
 }
