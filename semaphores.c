/*
Final Project
Bikramjit Garcha (991330905)
Harmanjeet Singh (991439186)
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define RAND_DIVISOR 100000000
#define BUFFER_SIZE 5
#define true 1

pthread_mutex_t bufferMutex;
sem_t full; 
sem_t empty;

pthread_t threadID;       //Thread ID
pthread_attr_t attribute; //Set of thread attributes

void *producer(void *param); // the producer thread 
void *consumer(void *param); // the consumer thread 

/* the buffer */
typedef int buffer_item;
buffer_item buffer[BUFFER_SIZE];
int buffer_index;

void initialize() {

	buffer_index = 0;
	pthread_mutex_init(&bufferMutex, NULL); // crate the mutex 
	sem_init(&full, 0, 0); // full semaphore and initalized to 0
	sem_init(&empty, 0, BUFFER_SIZE); // empty semaphore and initalized to buffer_size
	pthread_attr_init(&attribute); 

}

/* insert item into bufferreturn 0 if successful, otherwisereturn -1 indicating an error condition */
int insert_item(buffer_item item) {
	if (buffer_index < BUFFER_SIZE){
		buffer[buffer_index] = item;
		buffer_index++;
		return 0;
	}else{
		printf("Buffer Overflow");
		return -1;
	}
}

int remove_item(buffer_item *item) {
	if (buffer_index > 0){
		*item = buffer[(buffer_index-1)];
		buffer_index--;
	}else{
		printf("Buffer underflow");
		return -1;
	}
	return 0;
/* remove an object from bufferplacing it in itemreturn 0 if successful, otherwisereturn -1 indicating an error condition */
}

void *producer(void *param) {   
	buffer_item item;   
	printf("p\n");
	while (true) {      
		/* sleep for a random period of time */     
		// sleep(rand()); 
		int rNum = rand() / RAND_DIVISOR;
      	sleep(rNum);     
		/* generate a random number */      
		item = rand();

		sem_wait(&empty);
		pthread_mutex_lock(&bufferMutex);

		if (insert_item(item)){          
			fprintf(stderr, "report error condition"); 
		}else {        
			printf("producer produced %d\n",item);   
		}
		pthread_mutex_unlock(&bufferMutex);
		sem_post(&full);
	}
}

void *consumer(void *param) {   
	buffer_item item;   

	while (true) {
		   printf("c\n"); 
		/* sleep for a random period of time */      
		//sleep(rand()); 

		int rNum = rand() / RAND_DIVISOR;
      	sleep(rNum);

		sem_wait(&full);
		pthread_mutex_lock(&bufferMutex);

		if (remove_item(&item)) {        
			 fprintf(stderr, "report error condition");
      	}else {        
			printf("consumer consumed %d\n",item);  
		}

		pthread_mutex_unlock(&bufferMutex);
		sem_post(&empty);
	}
}

int main(int argc, char *argv[]) {

	/* 1. Get command line arguments  argv[1],argv[2],argv[3] */
	if(argc != 4){
		printf("Sorry sir/maam this program cannot execute due to the fact that there are not enough arguments.\nPlease I request that you next time enter in some numbers as an argument so this program can execute with joy.\nThanks! and have a wonderful day. :) \n");
	exit(1);
	}

	int sleepTime = atoi(argv[1]); //How long to sleep before terminating
	int producerThreads = atoi(argv[2]); // number of producer therads 
	int consumerThreads = atoi(argv[3]); // number of consumer therads


	/* 2. Initialize buffer */

	initialize();

	/* 3. Create producer thread(s) */

	for(int i = 0; i < producerThreads; i++) {	
      pthread_create(&threadID,&attribute,producer,NULL);
    }

	/* 4. Create consumer thread(s) */

    for(int i = 0; i < consumerThreads; i++) {
      pthread_create(&threadID,&attribute,consumer,NULL);
    }

	/* 5. Sleep */

    sleep(sleepTime);

	/* 6. Exit */

    printf("Exit the program\n");
	exit(0); 
	
}
