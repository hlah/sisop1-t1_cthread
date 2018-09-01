#include "../include/cthread_internal.h"
#include <stdio.h>

TCB_t* cthread_create_main_thread() {
	if( !cthread_inicializado ) {
		///// obtém contexto da main
		// cria novo TCB
		printf("Creating context for main...");
		cthread_main_thread.tid = 0;
		cthread_main_thread.state = CTHREAD_STATE_CREATION;
		cthread_main_thread.prio = CTHREAD_LOW_PRIORITY;
		cthread_main_thread.data = NULL;
		getcontext(&(cthread_main_thread.context));
		cthread_executing_thread = &cthread_main_thread;
		printf(" created!\n");

		cthread_inicializado = 1;
		 
		return &cthread_main_thread;
	}

	return NULL;
}
