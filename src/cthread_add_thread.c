#include "../include/cthread_internal.h"

int cthread_add_thread(TCB_t* thread_info) {
	// coloca na fila de criados
	AppendFila2(&cthread_created_fifo, (void*) thread_info);
	return 0;
}
