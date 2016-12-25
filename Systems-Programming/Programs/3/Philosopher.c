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
#include "Philosopher.h"

//global variables
philosopher *phil;
int count_eating = 0;
int N;

////////////////////////////////////////////////////////////////////////////////////////////////////helper functions

void take_fork(int i){
	sem_wait(&phil->lock); 
	phil->state[i] = HUNGRY;
	printf("process %d hungry \n",i);
	test(i);
	if(phil->state[i] == EATING){
		count_eating++;
		printf("process %d eating for %d time\n",i,count_eating);
	}
	sem_post(&phil->lock);
	sem_wait(&phil->philosopher_lock[i]); 
}

void put_fork(int i){
	sem_wait(&phil->lock); 
	phil->state[i] = THINKING;
	printf("process %d thinking \n",i);
	test(LEFT);
	test(RIGHT);
	sem_post(&phil->lock);
}

void test(int i){
	if (phil->state[i] == HUNGRY && phil->state[LEFT] != EATING && phil->state[RIGHT] != EATING)
		phil->state[i] = EATING;
		sem_post(&phil->philosopher_lock[i]); 
	
}

void think(){
	sleep(2);
}

void eat(){
	sleep(2);
}

////////////////////////////////////////////////////////////////////////////////////////////////////Main fucntion

int main(int argc,char *argv[])
{
	barrier *bar;

	int fd = open("philosophers.txt", O_RDWR, 0666);
	lseek(fd,sizeof(struct philosopher)-1,SEEK_SET);
	ftruncate(fd, sizeof(philosopher));
	// turn the file into shared memory
	phil = mmap( NULL, sizeof(struct philosopher), PROT_READ|PROT_WRITE, 
                 MAP_SHARED, fd, 0);

	int fd_b = open("barrier.txt", O_RDWR, 0666);
	lseek(fd_b,sizeof(struct barrier)-1,SEEK_SET);
	ftruncate(fd_b, sizeof(barrier));
	// turn the file into shared memory
	bar = mmap( NULL, sizeof(struct barrier), PROT_READ|PROT_WRITE, 
                 MAP_SHARED, fd_b, 0);

	//barrier sink
	sem_wait(&bar->lock_m); 
	bar->counter_b++;
	sem_post(&bar->lock_m);  

	while(1){
		printf("barrier sink, wait a while\n");
		if (bar->counter_b == atoi(argv[2])){
			sem_post(&bar->lock_b);  
			break;
		}
	}
 
	sem_wait(&bar->lock_b);             
	
	//variables in after barrier
	int j;
	int i = atoi(argv[1]);
	N = atoi(argv[2]);

	//call philosophers
	while (count_eating < atoi(argv[0])){
		think();
		take_fork(i);
		eat();
		put_fork(i);	
	}
	
	printf("end of process %d\n",atoi(argv[1]));

	sem_post(&bar->lock_b); 

	return 0;
}
