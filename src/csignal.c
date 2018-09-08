#include "../include/cthread_internal.h"

int csignal(csem_t *sem) {
    int i;
    PFILA2 fifoPrio;

    sem->count++;
    FirstFila2(sem->fila);

    for (i = CTHREAD_NUM_PRIORITY_LEVELS - 1; i >= 0; i--){ // verifica se há uma fila não vazia
        if (FirstFila2(fifoPrio = GetAtIteratorFila2(sem->fila)) != 0){
            cthread_sem_wakeup(sem, fifoPrio, i);
            return 0;
        }
        NextFila2(sem->fila);
    }

    return 0;
}
