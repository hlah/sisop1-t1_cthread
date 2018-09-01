#ifndef __cthread_internal__
#define __cthread_internal__

#include "support.h"
#include "cthread.h"
#include "cdata.h"

#include <ucontext.h>
#include <stdlib.h>

///// deifiniçoes
#define CTHREAD_NUM_PRIORITY_LEVELS 3

#define CTHREAD_LOW_PRIORITY 0
#define CTHREAD_MID_PRIORITY 1
#define CTHREAD_HIG_PRIORITY 2

#define CTHREAD_STATE_CREATION 	0
#define CTHREAD_STATE_APTO 		1
#define CTHREAD_STATE_EXEC 		2
#define CTHREAD_STATE_BLOCK		3
#define CTHREAD_STATE_END 		4

#define CTHREAD_STACK_SIZE		16*1024			// 16Kb

/////// funções internos da biblioteca ///////////
// inicializa cthread
int cthread_init();
// cria contexto da main
TCB_t* cthread_create_main_thread();
// adiciona novo thread
int cthread_add_thread(TCB_t* thread_info);
// escalona proximo thread
int cthread_schedule(TCB_t* current_thread);
// termina thread atual
void cthread_terminate();



/////// variaveis internas da cthread ////////
// indica se cthread foi inicializado
extern int cthread_inicializado;

// filas de prioridade
extern FILA2 cthread_priority_fifos[CTHREAD_NUM_PRIORITY_LEVELS];
// fila de criação
extern FILA2 cthread_created_fifo;
// thread em execução
extern TCB_t* cthread_executing_thread;

// main thread
extern TCB_t cthread_main_thread;

// id do proximo thread
extern int cthread_next_id;

// contexto de terminação
extern ucontext_t cthread_termination_context;

#endif
