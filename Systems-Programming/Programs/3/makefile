CC = gcc

all: Host Philosopher

Host: Host.c 
	${CC} -o Host Host.c -pthread -lrt -I.

Philosopher: Philosopher.c 
	${CC} -o Philosopher Philosopher.c -pthread -lrt -I.

clean:
	rm -f Host Philosopher
