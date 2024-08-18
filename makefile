CC = gcc

CFLAGS = -lm

all: t1

t1: t1.c
	$(CC) -o t1 t1.c $(CFLAGS)

clean:
	rm -f t1