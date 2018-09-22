#include "../include/cthread_internal.h"
#include <stdio.h>

int cthread_schedule(TCB_t* current_thread, int block) {
	int fifo_i=0;

	// move threads criados para fila de aptos
	FirstFila2(&cthread_created_fifo);
	TCB_t* next_created_thread;
	while( (next_created_thread = (TCB_t*)GetAtIteratorFila2(&cthread_created_fifo)) != NULL ) {
		// move para fifo de prioridade correspondente
		int priority = next_created_thread->prio;
		AppendFila2(&cthread_priority_fifos[priority], (void*)next_created_thread);
		DeleteAtIteratorFila2(&cthread_created_fifo);
		DEBUG_PRINT("Moved created thread %d (%p) to priority queue %d\n", next_created_thread->tid, next_created_thread, priority);
	}

	// coloca anterior na respectiva fila
	if( current_thread != NULL && !block) {
		AppendFila2(&cthread_priority_fifos[current_thread->prio], (void*)current_thread);
	}

	// obtém próximo thread
	TCB_t* next_thread = NULL;
	while( fifo_i < CTHREAD_NUM_PRIORITY_LEVELS && FirstFila2(&cthread_priority_fifos[fifo_i]) != 0 ) {
		fifo_i++;
	}
	if( fifo_i < CTHREAD_NUM_PRIORITY_LEVELS ) {
		next_thread = (TCB_t*)GetAtIteratorFila2(&cthread_priority_fifos[fifo_i]);
		DEBUG_PRINT("next thread: %p\n", next_thread);
	}

	
	if( next_thread != NULL ) {
		// coloca como thread em execução
		cthread_executing_thread = next_thread;
		// remove novo da fila
		DeleteAtIteratorFila2(&(cthread_priority_fifos[fifo_i]));
		if( current_thread != NULL ) {
			// swap contexts
			DEBUG_PRINT("Swapping contexts from thread %d to thread %d!\n", current_thread->tid, next_thread->tid);
			if( swapcontext( &(current_thread->context), &(next_thread->context) ) != 0 ) {
				return -1;
			}
		} else {
			// set context
			DEBUG_PRINT("Swapping context from terminated thread to thread %d!\n", next_thread->tid);
			if( setcontext( &(next_thread->context) ) != 0 ) {
				return -1;
			}
		}

	} else {
		DEBUG_PRINT("next thread is NULL!!\n");
		// continua current thread (não faz nada)
	}


	return 0;
}
