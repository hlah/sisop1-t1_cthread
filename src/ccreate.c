#include "../include/cthread_internal.h"

#include <stdio.h>

int ccreate (void* (*start)(void*), void *arg, int prio) {
	// inicializa cthread
	cthread_init();

	// cria novo thread
	printf("Creating new thread...");
	TCB_t* thread_info = (TCB_t*) malloc(sizeof(TCB_t));
	thread_info->tid = cthread_next_id++;
	thread_info->state = CTHREAD_STATE_CREATION;
	thread_info->prio = prio;
	thread_info->data = NULL;
	if( getcontext(&(thread_info->context)) != 0) {
		return -1;
	}
	(thread_info->context).uc_stack.ss_sp = malloc(CTHREAD_STACK_SIZE);
	(thread_info->context).uc_stack.ss_size = CTHREAD_STACK_SIZE;
	(thread_info->context).uc_link = &cthread_termination_context;				
	makecontext(&(thread_info->context), (void*)(int)start, 1, (int*)arg);
	printf(" created! (tid=%d)\n", thread_info->tid);
	cthread_add_thread(thread_info);

	// cria main thread
	cthread_create_main_thread();

	// escalona thread
	cthread_schedule(cthread_executing_thread);
	
	return 0;
}
