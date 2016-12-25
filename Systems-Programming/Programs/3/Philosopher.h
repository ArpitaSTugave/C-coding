///////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////code by Arpita S Tugave
///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

#ifndef cons_var
#define EATING 2
#define HUNGRY 1
#define THINKING 0
#define LEFT (i+N-1)%N
#define RIGHT (i+1)%N
#endif

typedef struct philosopher{
	sem_t philosopher_lock[BUFSIZ] , lock;
	int state[BUFSIZ];
	int counter;
}philosopher;

typedef struct barrier{
	sem_t lock_b, lock_m;
	int counter_b;
}barrier;
