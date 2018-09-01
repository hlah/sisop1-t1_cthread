#include "../include/cthread_internal.h"

int cthread_check_priority(int prio) {
	int i;
	for(i=prio+1; i<CTHREAD_NUM_PRIORITY_LEVELS; i++) {
		if( FirstFila2(&cthread_priority_fifos[i]) == 0 ) {
			return 1;
		}
	}
	return 0;
}
