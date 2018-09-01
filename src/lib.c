
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/support.h"
#include "../include/cthread.h"
#include "../include/cdata.h"

#include <ucontext.h>

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
int cthread_inicializado = 0;

// filas de prioridade
FILA2 cthread_priority_fifos[CTHREAD_NUM_PRIORITY_LEVELS];
// fila de criação
FILA2 cthread_created_fifo;
// thread em execução
TCB_t* cthread_executing_thread = NULL;

// id do proximo thread
int cthread_next_id = 1;

// contexto de terminação
ucontext_t cthread_termination_context;



int ccreate (void* (*start)(void*), void *arg, int prio) {
	// inicializa cthread
	cthread_init();

	// cria novo thread
	printf("Creating new thread...");
	TCB_t* thread_info = (TCB_t*) malloc(sizeof(TCB_t));
	thread_info->tid = cthread_next_id++;
	thread_info->state = CTHREAD_STATE_CREATION;
	thread_info->prio = prio;
	thread_info->data = NULL;
	getcontext(&(thread_info->context));
	(thread_info->context).uc_stack.ss_sp = malloc(CTHREAD_STACK_SIZE);
	(thread_info->context).uc_stack.ss_size = CTHREAD_STACK_SIZE;
	(thread_info->context).uc_link = &cthread_termination_context;				
	makecontext(&(thread_info->context), (void*)(int)start, 1, (int*)arg);
	printf(" created! (tid=%d)\n", thread_info->tid);
	cthread_add_thread(thread_info);

	// cria main thread
	cthread_create_main_thread();

	// escalona thread
	cthread_schedule(cthread_executing_thread);
	
	return 0;
}

int csetprio(int tid, int prio) {
	return -1;
}

int cyield(void) {
	return -1;
}

int cjoin(int tid) {
	return -1;
}

int csem_init(csem_t *sem, int count) {
	return -1;
}

int cwait(csem_t *sem) {
	return -1;
}

int csignal(csem_t *sem) {
	return -1;
}

int cidentify (char *name, int size) {
	strncpy (name, "Sergio Cechin - 2017/1 - Teste de compilacao.", size);
	return 0;
}



int cthread_init() {
	if( !cthread_inicializado ) {
		int i;
		// iniciliza filas de prioridade
		for(i = 0; i<CTHREAD_NUM_PRIORITY_LEVELS; i++) {
			printf("Creating fifo %d\n", i);
			CreateFila2(&cthread_priority_fifos[i]);
		}
		// inicializa fila de criação
		printf("Creating 'created' fifo.\n");
		CreateFila2(&cthread_created_fifo);
		// cria contexto de teminação
		printf("Creating termination context.\n");
		getcontext(&cthread_termination_context);
		cthread_termination_context.uc_stack.ss_sp = malloc(CTHREAD_STACK_SIZE);
		cthread_termination_context.uc_stack.ss_size = CTHREAD_STACK_SIZE;
		cthread_termination_context.uc_link = NULL;	
		makecontext(&cthread_termination_context, cthread_terminate, 0);
	}

	return 0;
}

TCB_t* cthread_create_main_thread() {
	if( !cthread_inicializado ) {
		///// obtém contexto da main
		// cria novo TCB
		printf("Creating context for main...");
		TCB_t* main_thread = (TCB_t*) malloc(sizeof(TCB_t));
		main_thread->tid = 0;
		main_thread->state = CTHREAD_STATE_CREATION;
		main_thread->prio = CTHREAD_LOW_PRIORITY;
		main_thread->data = NULL;
		getcontext(&(main_thread->context));
		cthread_add_thread(main_thread);
		cthread_executing_thread = main_thread;
		printf(" created!\n");

		cthread_inicializado = 1;
		 
		return main_thread;
	}

	return NULL;

}

int cthread_add_thread(TCB_t* thread_info) {
	// coloca na fila de criados
	AppendFila2(&cthread_created_fifo, (void*) thread_info);
	return 0;
}


int cthread_schedule(TCB_t* current_thread) {
	int fifo_i=CTHREAD_NUM_PRIORITY_LEVELS-1;

	// move threads criados para fila de aptos
	FirstFila2(&cthread_created_fifo);
	TCB_t* next_created_thread;
	while( (next_created_thread = (TCB_t*)GetAtIteratorFila2(&cthread_created_fifo)) != NULL ) {
		// move para fifo de prioridade correspondente
		int priority = next_created_thread->prio;
		AppendFila2(&cthread_priority_fifos[priority], (void*)next_created_thread);
		DeleteAtIteratorFila2(&cthread_created_fifo);
		printf("Moved created thread %d (%p) to priority queue %d\n", next_created_thread->tid, next_created_thread, priority);
	}

	// obtém próximo thread
	TCB_t* next_thread = NULL;
	while( fifo_i >= 0 && FirstFila2(&cthread_priority_fifos[fifo_i]) != 0 ) {
		fifo_i--;
	}
	if( fifo_i >= 0 ) {
		next_thread = (TCB_t*)GetAtIteratorFila2(&cthread_priority_fifos[fifo_i]);
		printf("next thread: %p\n", next_thread);
	}

	
	if( next_thread != NULL ) {
		// coloca como thread em execução
		cthread_executing_thread = next_thread;
		// remove novo da fila
		DeleteAtIteratorFila2(&(cthread_priority_fifos[fifo_i]));
		if( current_thread != NULL ) {
			// coloca anterior na respectiva fila
			AppendFila2(&cthread_priority_fifos[current_thread->prio], (void*)current_thread);
			// swap contexts
			printf("Swapping contexts from thread %d to thread %d!\n", current_thread->tid, next_thread->tid);
			swapcontext( &(current_thread->context), &(next_thread->context) );
		} else {
			// set context
			printf("Swapping context from terminated thread to thread %d!\n", next_thread->tid);
			setcontext( &(next_thread->context) );
		}

	} else {
		printf("next thread is NULL!!\n");
		// continua current thread (não faz nada)
	}


	return 0;
}

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
