#include "../include/cthread_internal.h"

/////// variaveis internas da cthread ////////
// indica se cthread foi inicializado
int cthread_inicializado = 0;

// filas de prioridade
FILA2 cthread_priority_fifos[CTHREAD_NUM_PRIORITY_LEVELS];
// fila de criação
FILA2 cthread_created_fifo;
// thread em execução
TCB_t* cthread_executing_thread = NULL;

// main thread
TCB_t cthread_main_thread;

// id do proximo thread
int cthread_next_id = 1;

// contexto de terminação
ucontext_t cthread_termination_context;
