#include "../include/cthread_internal.h"

#include <stdio.h>

int csem_init(csem_t *sem, int count) {
    if (count > 0){
        int i;
        PFILA2 fifoPrio[CTHREAD_NUM_PRIORITY_LEVELS];
	
	DEBUG_PRINT("Creating new semaphore...\n");
        CreateFila2(sem -> fila);
        for(i = 0; i < CTHREAD_NUM_PRIORITY_LEVELS; i++) // inicializa uma fila de bloqueados por prioridade
            CreateFila2(fifoPrio[i]);
	for(i = 0; i < CTHREAD_NUM_PRIORITY_LEVELS; i++) // adiciona filas de prioridade a fila principal
	    AppendFila2(sem -> fila, (void*) fifoPrio[i]);
        sem -> count = count;
	DEBUG_PRINT("Semaphore created!\n");
        return 0;
    }
    return -1; // erro count <= 0
}
