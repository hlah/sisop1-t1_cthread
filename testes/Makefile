#
# Makefile para programas de teste
# 

CC=gcc
LIB_DIR=../lib
CFLAGS=-lcthread -Wall -m32

all: testa_inicio testa_yield testa_setprio testa_join
	
testa_inicio: testa_inicio.c $(LIB_DIR)/libcthread.a
	$(CC) -o testa_inicio testa_inicio.c -L$(LIB_DIR) $(CFLAGS)

testa_yield: testa_yield.c $(LIB_DIR)/libcthread.a
	$(CC) -o testa_yield testa_yield.c -L$(LIB_DIR) $(CFLAGS)

testa_setprio: testa_setprio.c $(LIB_DIR)/libcthread.a
	$(CC) -o testa_setprio testa_setprio.c -L$(LIB_DIR) $(CFLAGS)

testa_join: testa_join.c $(LIB_DIR)/libcthread.a
	$(CC) -o testa_join testa_join.c -L$(LIB_DIR) $(CFLAGS)

.PHONY: all clean testa_inicio testa_setprio testa_join testa_yield
	
clean:
	rm -rf testa_inicio testa_yield testa_setprio testa_join *.o *~
