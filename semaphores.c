/*
Final Project
Bikramjit Garcha (991330905)
Harmanjeet Singh (991439186)
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

/* the buffer */
typedef int buffer_item;
#define BUFFER_SIZE 5
int buffer_index;
buffer_item buffer[BUFFER_SIZE];

int insert item(buffer_item item) {
	if (buffer_index < BUFFER_SIZE){
		buffer[buffer_index++] = item;
	}else{
		printf("Buffer Overflow")
		return -1;
	}
	return 0;
/* insert item into bufferreturn 0 if successful, otherwisereturn -1 indicating an error condition */
}

int remove item(buffer item *item) {
	if (buffer_index > 0){
		return buffer[--buffer_index];
	}else{
		printf("Buffer underflow")
		return -1;
	}
	return 0;
/* remove an object from bufferplacing it in itemreturn 0 if successful, otherwisereturn -1 indicating an error condition */
}

void *producer(void *param) {   
	buffer item item;   

	while (true) {      
		/* sleep for a random period of time */     
		 sleep(...);      
		/* generate a random number */      
		item = rand();      
		if (insert item(item))         
			fprintf("report error condition");      
		else         
			printf("producer produced %d\n",item);   
		}
}

void *consumer(void *param) {   
	buffer item item;   

	while (true) {     
		/* sleep for a random period of time */      
		sleep(...);      
		if (remove item(&item))         
			fprintf("report error condition");
      		else         
			printf("consumer consumed %d\n",item);  
	}
}

int main(int argc, char *argv[]) {

	/* 1. Get command line arguments  argv[1],argv[2],argv[3] */
	
	/* 2. Initialize buffer */
	/* 3. Create producer thread(s) */
	/* 4. Create consumer thread(s) */
	/* 5. Sleep */
	/* 6. Exit */

	int n; 
	semaphore mutex = 1; 
	semaphore empty = n; 
	semaphore full = 0


	return 0; 
	
}
