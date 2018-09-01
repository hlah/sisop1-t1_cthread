#include "../include/cthread_internal.h"
#include <stdio.h>

TCB_t* cthread_create_main_thread() {
	if( !cthread_inicializado ) {
		///// obtém contexto da main
		// cria novo TCB
		printf("Creating context for main...");
		TCB_t* main_thread = (TCB_t*) malloc(sizeof(TCB_t));
		main_thread->tid = 0;
		main_thread->state = CTHREAD_STATE_CREATION;
		main_thread->prio = CTHREAD_LOW_PRIORITY;
		main_thread->data = NULL;
		getcontext(&(main_thread->context));
		cthread_add_thread(main_thread);
		cthread_executing_thread = main_thread;
		printf(" created!\n");

		cthread_inicializado = 1;
		 
		return main_thread;
	}

	return NULL;

}
