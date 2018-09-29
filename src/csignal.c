#include "../include/cthread_internal.h"

#include <stdio.h>

int csignal(csem_t *sem) {

	TCB_t* next = NULL;
	TCB_t* iter = NULL;
	int prio = CTHREAD_NUM_PRIORITY_LEVELS;

    sem->count++;
    DEBUG_PRINT("Thread %d leaving critical sector\n", cthread_executing_thread->tid);

	FirstFila2(sem->fila);

	// acha proximo na espera
	while( (iter = (TCB_t*)GetAtIteratorFila2(sem->fila)) != NULL ) {
		if( iter->prio < prio ) {
			next = iter;
			prio = iter->prio;
		}
		NextFila2(sem->fila);
	}

	// se há próximo
	if( next != NULL ) {
		next->state = CTHREAD_STATE_APTO;

		// remove da lista de espera
		while( (iter = (TCB_t*)GetAtIteratorFila2(sem->fila)) != next ) {
			NextFila2(sem->fila);
		}
		DeleteAtIteratorFila2(sem->fila);

		// adiciona a fila de prioridades
		AppendFila2(&cthread_priority_fifos[next->prio], (void*) next);

		// se prioridade maior, reescalona
		if( next->prio < cthread_executing_thread->prio ) {
			cthread_schedule(cthread_executing_thread, 0);
		}

	}

    return 0;
}
