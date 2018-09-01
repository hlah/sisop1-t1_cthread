#include "../include/cthread_internal.h"
#include <stdio.h>

int cthread_init() {
	if( !cthread_inicializado ) {
		int i;
		// iniciliza filas de prioridade
		for(i = 0; i<CTHREAD_NUM_PRIORITY_LEVELS; i++) {
			DEBUG_PRINT("Creating fifo %d\n", i);
			CreateFila2(&cthread_priority_fifos[i]);
		}
		// inicializa fila de criação
		DEBUG_PRINT("Creating 'created' fifo.\n");
		CreateFila2(&cthread_created_fifo);
		// cria contexto de teminação
		DEBUG_PRINT("Creating termination context.\n");
		getcontext(&cthread_termination_context);
		cthread_termination_context.uc_stack.ss_sp = malloc(CTHREAD_STACK_SIZE);
		cthread_termination_context.uc_stack.ss_size = CTHREAD_STACK_SIZE;
		cthread_termination_context.uc_link = NULL;	
		makecontext(&cthread_termination_context, cthread_terminate, 0);
	}

	return 0;
}
