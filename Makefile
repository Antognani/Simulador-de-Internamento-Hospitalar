CC = gcc
CFLAGS = -g -Wall -Iinclude

EXEC = bin/hospital

SRCS = src/main.c src/simulacao.c src/estruturas.c src/io.c
OBJS = obj/main.o obj/simulacao.o obj/estruturas.o obj/io.o

all: $(EXEC)

$(EXEC): $(OBJS)
	@mkdir -p bin
	$(CC) $(CFLAGS) -o $@ $^

obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

.PHONY: all clean
