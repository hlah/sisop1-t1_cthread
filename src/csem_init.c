#include "../include/cthread_internal.h"

#include <stdio.h>

int csem_init(csem_t *sem, int count) {
    if (count > 0){
		DEBUG_PRINT("Creating new semaphore...\n");
		sem->fila = malloc(sizeof(FILA2));
		CreateFila2(sem->fila);
		sem->count = count;
		DEBUG_PRINT("Semaphore created!\n");
		return 0;
	}
    return -1; // erro count <= 0
}
