#include "../include/cthread_internal.h"
#include <stdio.h>
#include <assert.h>

// termina thread atual
void cthread_terminate() {
	DEBUG_PRINT("Terminating thread %d\n", cthread_executing_thread->tid);
	// se algum thread esperando join, recoloca na fifo de aptors
	if( cthread_executing_thread->data != NULL ) {
		TCB_t* joined_thread = (TCB_t*)cthread_executing_thread->data;
		AppendFila2(&cthread_priority_fifos[joined_thread->tid], (void*)joined_thread);
	}
	// libera memoria da stack
	assert(cthread_executing_thread->tid != 0);
	free((cthread_executing_thread->context).uc_stack.ss_sp);
	(cthread_executing_thread->context).uc_stack.ss_size = 0;
	// libera TCB
	free(cthread_executing_thread);
	cthread_executing_thread = NULL;
	// escalona proximo thread
	cthread_schedule(cthread_executing_thread, 0);


	DEBUG_PRINT("ERROR: THIS SHOULD NOT BE REACHED!!!!!\n");
	assert(0);

}
