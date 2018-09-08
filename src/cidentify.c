#include "../include/cthread_internal.h"
#include <string.h>

int cidentify (char *name, int size) {
	strncpy (name, "Gerente: Mateus Davi Simon - 00209411\nMembro 1: Artur Galvao Hallberg - 00246759", size);
	return 0;
}
