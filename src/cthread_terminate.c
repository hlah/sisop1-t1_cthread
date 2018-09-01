#include "../include/cthread_internal.h"
#include <stdio.h>
#include <assert.h>

// termina thread atual
void cthread_terminate() {
	printf("Terminating thread %d\n", cthread_executing_thread->tid);
	// libera memoria da stack
	assert(cthread_executing_thread->tid != 0);
	free((cthread_executing_thread->context).uc_stack.ss_sp);
	(cthread_executing_thread->context).uc_stack.ss_size = 0;
	// libera TCB
	free(cthread_executing_thread);
	cthread_executing_thread = NULL;
	
	/// RESETAR CONTEXTO ?

	// escalona proximo thread
	cthread_schedule(cthread_executing_thread);


	printf("ERROR: THIS SHOULD NOT BE REACHED!!!!!\n");

}
