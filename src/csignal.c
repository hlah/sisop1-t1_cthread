#include "../include/cthread_internal.h"

int csignal(csem_t *sem) {

    int i;
    PFILA2 fifoPrio;

    sem -> count++;

    if (sem -> count == 1){
        FirstFila2(sem->fila);
        for (i = 0; i < CTHREAD_NUM_PRIORITY_LEVELS; i++){ // verifica se há um processo bloqueado (fila não vazia)
            if (FirstFila2(fifoPrio = GetAtIteratorFila2(sem->fila)) != 0){
                return cthread_sem_wakeup(sem, fifoPrio);
            }
            NextFila2(sem->fila);
        }
    }
    return 0;
}
