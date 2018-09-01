#include "../include/cthread_internal.h"

int cyield() {
	// schedule
	return cthread_schedule(cthread_executing_thread, 0);
}
