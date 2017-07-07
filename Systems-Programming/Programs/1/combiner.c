 #include <stdlib.h> 
#include <stdio.h>

char *args1 = "./mapper";
char *args2 = "./reducer";

void readWriteEnd(int pfd1, int pfd2 , char *s , int flag);

int main(int argc, char **argv) 
{

	int pid, status, flag=1; 
	int fd[2]; 

	pipe(fd); 
	//Function used to call Mapper function
	readWriteEnd(fd[0],fd[1],args1,flag); 
	flag = 0;
	//Function used to call Reducer function
	readWriteEnd(fd[1] , fd[0], args2,flag);
	//close the pipe
	close(fd[0]); 
	close(fd[1]); 
	//check the status and of closed children and exit
	while ((pid = wait(&status)) != -1)
	fprintf(stderr, "process %d exits with %d \n", pid, WEXITSTATUS(status)); 

	exit(0); 

}

/* Function used to call Reducer and Mapper function*/
void readWriteEnd(int pfd1, int pfd2 , char *s , int flag)	
{

int pid; 

switch (pid = fork()) 
{ 

case 0:  //child
	dup2(pfd2, flag); 
	close(pfd1); 	
	execvp(s,NULL);

default: //parent
	break; 

case -1: 
	perror("fork");
	exit(1); 
} 
}
