#include "../include/cthread_internal.h"

#include <stdio.h>

int csetprio(int tid, int prio) {

	cthread_executing_thread->prio = prio;
	printf("Setting priority of current thread (%d) to %d.\n", cthread_executing_thread->tid, prio);

	// reescalona
	if( cthread_check_priority(prio) ) {
		cthread_schedule(cthread_executing_thread, 0);
	}

	return 0;
}
