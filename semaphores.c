/*
Final Project- Semaphores
Bikramjit Garcha (991330905)
Harmanjeet Singh (991439186)
*/

#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h>


#define BUFFER_SIZE 5
#define true 1

 /* the buffer */
typedef int buffer_item;
int buffer_index;
buffer_item buffer[BUFFER_SIZE];

/* defining semaphores and pthread */
pthread_mutex_t bufferMutex;
sem_t fullBuff;
sem_t emptyBuff;
pthread_t threadID; //Thread ID
pthread_attr_t attribute; //Set of thread attributes

void * producer(void * param); // the producer thread 
void * consumer(void * param); // the consumer thread 

/* insert item into bufferreturn 0 if successful, otherwisereturn -1 indicating an error condition */
int insert_item(buffer_item item) {

  if (buffer_index < BUFFER_SIZE) {
    buffer[buffer_index] = item;
    buffer_index++;
    return 0;
  } else {
    printf("Buffer Overflow \n");
    return -1;
  }

}

/* remove an object from bufferplacing it in itemreturn 0 if successful, otherwisereturn -1 indicating an error condition */
int remove_item(buffer_item * item) {

  if (buffer_index > 0) {
  	* item = buffer[(buffer_index - 1)];
    buffer_index--;
    return 0;
  } else {
    printf("Buffer underflow \n");
    return -1;
  }

}

void * producer(void * param) {

  buffer_item item;
  
  while (true) {
    /* sleep for a random period of time */
    sleep(rand() % 10);
    /* generate a random number */
    item = rand();

    sem_wait( & emptyBuff);
    pthread_mutex_lock( & bufferMutex);

    if (insert_item(item)) {
      fprintf(stderr, "report error condition \n");
    } else {
      printf("producer produced %d\n", item);
    }
    pthread_mutex_unlock( & bufferMutex);
    sem_post( & fullBuff);
  }
}

void * consumer(void * param) {

  buffer_item item;

  while (true) {
    /* sleep for a random period of time */
    sleep(rand() % 10);

    sem_wait( & fullBuff);
    pthread_mutex_lock( & bufferMutex);

    if (remove_item( & item)) {
      fprintf(stderr, "report error condition \n");
    } else {
      printf("consumer consumed %d\n", item);
    }

    pthread_mutex_unlock( & bufferMutex);
    sem_post( & emptyBuff);
  }
}

int main(int argc, char * argv[]) {

  /* 1. Get command line arguments  argv[1],argv[2],argv[3] */

  if (argc != 4) {
    printf("Sorry sir/maam this program cannot execute due to the fact that there are not enough arguments.\nPlease I request that you next time enter in some numbers as an argument so this program can execute with joy.\nThanks! and have a wonderful day. :) \n");
    exit(1);
  }

  int sleepTime = atoi(argv[1]); //How long to sleep before terminating
  int producerThreads = atoi(argv[2]); // number of producer therads 
  int consumerThreads = atoi(argv[3]); // number of consumer therads

  /* 2. Initialize buffer */

  buffer_index = 0;
  pthread_mutex_init( & bufferMutex, NULL); // create the mutex 
  sem_init(&fullBuff,0,0); // full semaphore and initalized to 0
  sem_init( & emptyBuff, 0, BUFFER_SIZE); // empty semaphore and initalized to buffer_size
  pthread_attr_init( & attribute);

  /* 3. Create producer thread(s) */

  for (int i = 0; i < producerThreads; i++) {
    pthread_create( & threadID, & attribute, producer, NULL);
  }

  /* 4. Create consumer thread(s) */

  for (int i = 0; i < consumerThreads; i++) {
    pthread_create(& threadID, & attribute, consumer, NULL);
  }

  /* 5. Sleep */

  sleep(sleepTime);

  /* 6. Exit */

  printf("Thank you Sir/Maam for using this wonderfully exquisite program created by Harmanjeet(991439186) and Bikramjit(991330905).\nThank you and have yourself a wonderfull day! =D\n");
  exit(0);

}