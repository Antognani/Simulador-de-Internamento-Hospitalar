#MAKEFILE
CC = gcc
CFLAGS = -g -Wall

EXEC = simulador

SRCS = main.c simulacao.c estruturas.c log.c

OBJS = $(SRCS:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC) processamento.log

.PHONY: all clean