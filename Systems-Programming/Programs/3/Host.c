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
//argument to be passed to the philosophers process
char *argv1[3];

////////////////////////////////////////////////////////////////////////////////////////////////////Main fucntion

int main(int argc,char *argv[])
{
	philosopher *phil;
	barrier *bar;
	int status, i;

	int fd = open("philosophers.txt", O_CREAT|O_TRUNC|O_RDWR, 0666);
	lseek(fd,sizeof(struct philosopher)-1,SEEK_SET);
	ftruncate(fd, sizeof(philosopher));
	// turn the file into shared memory
	phil = mmap( NULL, sizeof(struct philosopher), PROT_READ|PROT_WRITE, 
                 MAP_SHARED, fd, 0);

	int fd_b = open("barrier.txt", O_CREAT|O_TRUNC|O_RDWR, 0666);
	lseek(fd_b,sizeof(struct barrier)-1,SEEK_SET);
	ftruncate(fd_b, sizeof(barrier));
	// turn the file into shared memory
	bar = mmap( NULL, sizeof(struct barrier), PROT_READ|PROT_WRITE, 
                 MAP_SHARED, fd_b, 0);

	sem_init(&bar->lock_m, 0, 1); 
	sem_init(&bar->lock_b, 0, 1);

	sem_wait(&bar->lock_b);  

	sem_init(&phil->lock, 0, 1); 
	sem_init(&phil->philosopher_lock, 0, 5); 

	for (i = 0 ; i < atoi(argv[1]) ; i++){
		sleep(3);
		if(fork()==0){

			//parameters to be passed to philosophers
			char parameter1[32];
			sprintf(parameter1, "%d", atoi(argv[2]));
			argv1[0] = parameter1;
			char parameter2[32];
			sprintf(parameter2, "%d", i);
			argv1[1] = parameter2;
			char parameter3[32];
			sprintf(parameter3, "%d", atoi(argv[1]));
			argv1[2] = parameter3;

			execvp("./Philosopher", &argv1);
		}
		else{
			//if parent continue spawning children
			continue;
		}
	}

	//close all children
	for (i = 0 ; i < atoi(argv[1]) ; i++){
		//check the status and of closed children and exit
		wait(&status);
	}

	sem_destroy(&bar->lock_m);
	sem_destroy(&bar->lock_b);

	sem_destroy(&phil->lock);
	sem_destroy(&phil->philosopher_lock);

	return 0;
}
