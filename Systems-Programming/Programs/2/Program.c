///////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////code by Arpita S Tugave
///////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define TRUE 1
#define FALSE 0

//////////////////////////////////////////////////////////////////////////////////////////initializations

//you can enter 1000 different words
enum { MAXLINES = 1000 };
// your bounded buffer size is 5
enum { MAXBUFF = 5};
pthread_mutex_t MapperPoolLock = PTHREAD_MUTEX_INITIALIZER , ReducerLock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t SummarizerLock = PTHREAD_MUTEX_INITIALIZER , CountLock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t MapperPoolCondition, MapperCondition , ReducerCondition , SummarizerCondition , CountCondition;

char MapperPoolBUffer[MAXBUFF][MAXLINES][BUFSIZ] , ReducerBuffer[MAXBUFF][MAXLINES][BUFSIZ];
char SummarizerBuffer[MAXBUFF][MAXLINES][BUFSIZ] , LetterCountBuffer[MAXBUFF][BUFSIZ];
int readMapper = FALSE , readReducer = FALSE , readSummarizer = FALSE , readSummarizerLetter = FALSE;
int countMapperPool = 0 , count_Mapperbuff =0, count_Reducerbuff =0 ,  readCount = FALSE;

/////////////////////////////////////////////////////////////////////////////////////////helper functions

/* appends three strings */
char* stradd(const char* string1, const char* string2, const char* string3){
	size_t len = strlen(string1) + strlen(string2) + strlen(string3);
	char *return_r = (char*)malloc(len * sizeof(char) + 1);
	*return_r = '\0';
	return strcat(strcat(strcat(return_r, string1) ,string2) ,string3);
}

/* converts int to string */
char *itoa (int value, char *result, int base){
	// check for base validity
	if (base < 2 || base > 36) { *result = '\0'; return result; }

	char* ptr = result, *ptr1 = result, tmp_char;
	int tmp_value;

	do {
	        tmp_value = value;
	        value /= base;
	        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
	} while ( value );

	// Negative sign applied
	if (tmp_value < 0) *ptr++ = '-';
		*ptr-- = '\0';
   
	while (ptr1 < ptr) {
	        tmp_char = *ptr;
	        *ptr--= *ptr1;
	        *ptr1++ = tmp_char;
    	}
    	return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////Mapper pool updater

void * MapperPoolUpdater(void *fileName)
{

	char buffer[BUFSIZ], name[MAXLINES][BUFSIZ], c= 'a' , s = 'a', ch;
	int count_name = 0;

	//read the file and store into a array
	FILE *fp = fopen(fileName, "r");

	//read from the file and store in the array "name
	if (fp == 0) {
		fprintf(stderr, "failed to open txt file \n");
		exit(1);
	}

	do
	{
		ch = fscanf(fp, "%s", buffer);
		strcpy(name[count_name],buffer);
		//printf("%s %d \n", buffer, count_name);
		count_name++;

	}while (ch != EOF);

	int count1 = count_name-2;
	count_name = 0;

	//transfer read file into Mapper Pool Buffer
	while(count_name<count1){
	
		while(readMapper);
		pthread_mutex_lock(&MapperPoolLock);

		char *p = name[count_name];
		s = *p;
		c = s;

		countMapperPool = 0;

		//check if words start with the same alphabet
		while(c == s){
			//make the buffer bounded
			count_Mapperbuff = count_Mapperbuff%MAXBUFF;
			if(count_name>count1)
			break;
			strcpy(MapperPoolBUffer[count_Mapperbuff][countMapperPool],name[count_name]);
			//printf(" string count %d buffer count %d string %s\n", count_Mapperbuff , countMapperPool , MapperPoolBUffer[count_Mapperbuff][countMapperPool]);
			countMapperPool++;
			count_name++;
			char *p = name[count_name];
			s = *p;
		}

		count_Mapperbuff++;

		readMapper = TRUE;
		pthread_mutex_unlock(&MapperPoolLock);
		pthread_cond_signal(&MapperPoolCondition);
	}

}

///////////////////////////////////////////////////////////////////////////////////////////////////Mapper

void * Mapper()
{

        while(1){
			//get the loack of Mapper Pool Buffer
		        pthread_mutex_lock(&MapperPoolLock);
		        while(!readMapper)
                        pthread_cond_wait(&MapperPoolCondition,&MapperPoolLock);

			int count_stop = countMapperPool-1;
			int count_buff = count_Mapperbuff-1;
			int count = 0;
			char tempMapper_buffer[MAXLINES][BUFSIZ];
			
			//store in temporary buffer from Mapper Pool 
			while(count <= count_stop)
			{
				strcpy(tempMapper_buffer[count],MapperPoolBUffer[count_buff][count]);
				//printf(" string count %d string %s\n", count , tempMapper_buffer[count]);
				count++;
			}

                        readMapper = FALSE;
                        pthread_mutex_unlock(&MapperPoolLock);

			//get the lock to Reducer Pool
			while(readReducer);
		        pthread_mutex_lock(&ReducerLock);

			count = 0;
			while(count <= count_stop)
			{
				char *pos;
				char *p = tempMapper_buffer[count];

				//for last line; remove new line character
				if ((pos=strchr(p, '\n')) != NULL)
		     		p[strlen(p)-2] =  0;

				char *str = stradd("(" , p,",1)"); 
				strcpy(ReducerBuffer[count_buff][count],str);

				//printf(" buffer count % d string count %d string %s \n", count_buff , count , ReducerBuffer[count_buff][count]);
				count++;
			}

		        readReducer = TRUE;
		        pthread_mutex_unlock(&ReducerLock);
		        pthread_cond_signal(&ReducerCondition);

	}
}

////////////////////////////////////////////////////////////////////////////////////////////////// Reducer funtion
void * Reducer()
{
        while(1){
			//get the lock to Reducer Pool
		        pthread_mutex_lock(&ReducerLock);
		        while(!readReducer)
                        pthread_cond_wait(&ReducerCondition,&ReducerLock);

			int count_stop = countMapperPool-1;
			int count_buff = count_Mapperbuff-1;
			int count = 0;
			char tempReducer_buffer[MAXLINES][BUFSIZ];

			//store in temporary buffer from Mapper Pool
			while(count <= count_stop)
			{
				strcpy(tempReducer_buffer[count],ReducerBuffer[count_buff][count]);
				//printf(" string count %d string %s\n", count , tempReducer_buffer[count]);
				count++;
			}

                        readReducer = FALSE;
                        pthread_mutex_unlock(&ReducerLock);

			//get the lock to Summarizer Pool
			while(readSummarizer && readSummarizerLetter);
			pthread_mutex_lock(&SummarizerLock);

			int count_words = 0, i = 0, j = 0;
			count_Reducerbuff = 0;

			while (i <= count_stop) {
				count_words = 1;

				//count the number of words in the array
				for (j = i + 1; j <= count_stop; j++) {
					if (strcmp(tempReducer_buffer[i], tempReducer_buffer[j]) == 0 ) {
						count_words++;
						//equate detected string to space character; for not to be detected again
						strcpy(tempReducer_buffer[j]," ");
					}
				}
				//printf("%d %s \n", count_words,tempReducer_buffer[i]);

				if(strcmp(tempReducer_buffer[i], " ") != 0){
					char snum[2];
					itoa(count_words, snum, 10);
					//truncate thelast two characters of the string
			       		char *p = tempReducer_buffer[i];
					p[strlen(p)-2] =  0;

					p = stradd(p,snum,")"); //assign key
					strcpy(SummarizerBuffer[count_buff][count_Reducerbuff],p);
					//printf("%d %d %s \n", count_buff, count_Reducerbuff, SummarizerBuffer[count_buff][count_Reducerbuff]);
					count_Reducerbuff++;

		               	}

				i = i + 1;
			}

			readSummarizer = TRUE;
			readSummarizerLetter = TRUE;
			pthread_mutex_unlock(&SummarizerLock);
			pthread_cond_broadcast(&SummarizerCondition);

	}
}


////////////////////////////////////////////////////////////////////////////////////////////////// Word Count funtion
void * WordCount()
{

	FILE *f = fopen("wordCount.txt", "w");

        while(1){
			//get the lock to Summarizer Pool
		        pthread_mutex_lock(&SummarizerLock);
		        while(!readSummarizer)
                        pthread_cond_wait(&SummarizerCondition,&SummarizerLock);

			int count_stop = count_Reducerbuff-1;
			int count = 0;
			int count_buff = count_Mapperbuff-1;
			char tempWordCountWriter_buffer[MAXLINES][BUFSIZ];

			//printf("recieved \n");
			FILE *f = fopen("wordCount.txt", "a+");

			if (f == NULL)
			{
			    printf("Error opening file!\n");
			    exit(1);
			}

			while(count <= count_stop)
			{
				strcpy(tempWordCountWriter_buffer[count],SummarizerBuffer[count_buff][count]);
				const char *text = SummarizerBuffer[count_buff][count];
				fprintf(f, "%s\n", text);
				//printf(" string count %d string %s\n", count_buff , tempWordCountWriter_buffer[count]);
				count++;
			}

			fclose(f);

		        readSummarizer = FALSE;
                        pthread_mutex_unlock(&SummarizerLock);
	}

	fclose(f);
}

////////////////////////////////////////////////////////////////////////////////////////////////// Summarizer funtion
void * Summarizer()
{

        while(1){
			//get the lock to Summarizer Pool
		        pthread_mutex_lock(&SummarizerLock);
		        while(!readSummarizerLetter)
                        pthread_cond_wait(&SummarizerCondition,&SummarizerLock);


			int count_stop = count_Reducerbuff-1;
			int count = 0;
			int count_buff = count_Mapperbuff-1;
			char tempSummarizer_buffer[MAXLINES][BUFSIZ];

			while(count <= count_stop)
			{
				strcpy(tempSummarizer_buffer[count],SummarizerBuffer[count_buff][count]);
				//printf(" string count %d string %s\n", count , tempSummarizer_buffer[count]);
				count++;
			}

		        readSummarizerLetter = FALSE;
                        pthread_mutex_unlock(&SummarizerLock);

			//get the lock to Count Pool
			while(readCount);
		        pthread_mutex_lock(&CountLock);

			int total = 0;
			char c;
			count = 0;
			c = tempSummarizer_buffer[count][1];
			char word[4];
			word[0] = '(';
			word[1] = c;
			word[2] = ',';

			while(count <= count_stop)
			{
				char *p = tempSummarizer_buffer[count];
				int i = 0;
				sscanf(p,"%*[^0123456789]%d", &i);
				//printf(" string %d \n", i);
				count++;
				total = total + i;	
			}

			char snum[10];
			itoa(total, snum, 10);
			char *p = stradd(word,snum,")"); 

			strcpy(LetterCountBuffer[count_buff],p);
			printf("%d word: %s \n", count_buff, LetterCountBuffer[count_buff]);

		        readCount = TRUE;
		        pthread_mutex_unlock(&CountLock);
		        pthread_cond_signal(&CountCondition);


	}

}

////////////////////////////////////////////////////////////////////////////////////////////////// Letter Count Writer funtion
void * CountWriter()
{

	FILE *f = fopen("letterCount.txt", "w");

        while(1){
			//get the loack of Count Pool
		        pthread_mutex_lock(&CountLock);
		        while(!readCount)
                        pthread_cond_wait(&CountCondition,&CountLock);

			int count_buff = count_Mapperbuff-1;

			//printf("recieved \n");
			FILE *f = fopen("letterCount.txt", "a+");

			if (f == NULL)
			{
			    printf("Error opening file!\n");
			    exit(1);
			}

				const char *text = LetterCountBuffer[count_buff];
				fprintf(f, "%s\n", text);
				//printf(" string count %d string %s\n", count , tempWordCountWriter_buffer[count]);

			fclose(f);

                        readCount = FALSE;
                        pthread_mutex_unlock(&CountLock);
	}

	fclose(f);

}
////////////////////////////////////////////////////////////////////////////////////////////////////Main fucntion

int main(int argc,char *argv[])
{

	//initializations
	int t , Mapper_NUMTHREADS , Reducer_NUMTHREADS , Summarizer_NUMTHREADS;
	char *fileName;

        if (argc != 5) {
            printf("Usage: %s filename m n l",argv[0]);
            return 1;
        }

	fileName = argv[1];
        Mapper_NUMTHREADS = atoi(argv[2]);
        Reducer_NUMTHREADS = atoi(argv[3]);
        Summarizer_NUMTHREADS = atoi(argv[4]);

	pthread_t MapperPoolUpdaterThread, MapperThread[Mapper_NUMTHREADS] , ReducerThread[Reducer_NUMTHREADS];
	pthread_t WordCountThread , SummarizerThread[Summarizer_NUMTHREADS] , CountThread;

	//initialize threads
        pthread_create(&MapperPoolUpdaterThread,NULL,MapperPoolUpdater,(void *) fileName);

	for(t=0; t<Mapper_NUMTHREADS; t++){
	      printf("In mapper: creating thread %ld\n", t);
	      pthread_create(&MapperThread[t], NULL, Mapper, NULL);
	}

	for(t=0; t<Reducer_NUMTHREADS; t++){
	      printf("In reducer: creating thread %ld\n", t);
	      pthread_create(&ReducerThread[t], NULL, Reducer, NULL);
	}


	pthread_create(&WordCountThread, NULL, WordCount, NULL);

	for(t=0; t<Summarizer_NUMTHREADS; t++){
	      printf("In summarizer: creating thread %ld\n", t);
	      pthread_create(&SummarizerThread, NULL, Summarizer, NULL);
	}

	pthread_create(&CountThread, NULL, CountWriter, NULL);

	//use join call to make main to wait
	pthread_join(MapperPoolUpdaterThread,NULL);

	for(t=0; t<Mapper_NUMTHREADS; t++){
	      pthread_join(&MapperThread[t], NULL);
	}

	for(t=0; t<Reducer_NUMTHREADS; t++){
	      pthread_join(&ReducerThread[t], NULL);
	}

	pthread_join(&WordCountThread, NULL);

	for(t=0; t<Summarizer_NUMTHREADS; t++){
		pthread_join(&SummarizerThread, NULL);
	}

	pthread_join(&CountThread, NULL);

        return 0;
}
