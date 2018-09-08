#include "../include/cthread_internal.h"

void cthread_sem_wakeup(csem_t* sem, PFILA2 fifoPrio, int priority){

    sem->count--;
    GetAtIteratorFila2(fifoPrio)->state = CTHREAD_STATE_APT;
    AppendFila2(&cthread_priority_fifos[priority], (void*) GetAtIteratorFila2(fifoPrio));
    DeleteAtIteratorFila2(fifoPrio);

    if (priority > cthread_executing_thread->prio) // checa prioridade do processo bloqueado
        cthread_schedule(cthread_executing_thread, 0);

}
