#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <math.h>

#define MAXSIZE 10

int buffer[MAXSIZE];
sem_t empty, full;
pthread_mutex_t mutex;
pthread_t prd[5], con[5];

void *producer(void *arg)
{
	sem_wait(&empty);
	pthread_mutex_lock(&mutex);
	buffer[*(int *)arg] = rand();
	sem_post(&full);
}

int main()
{
	pthread_mutex_init(&mutex, NULL);
	sem_init(&empty, 0, 5);
	sem_init(&full, 0, 0);

	// for(int i = 0; i < 5; i++){
	// 		pthread_create(&prd[i],NULL,producer,&i);
	// }
	// pthread_join()
}

// #include <pthread.h>
// #include <semaphore.h>
// #include <stdlib.h>
// #include <stdio.h>

// #define MaxItems 5
// #define BufferSize 5

// sem_t empty;
// sem_t full;
// pthread_mutex_t mutex; // used to create and manage a mutex (mutual exclusion) lock in multithreaded programming

// int buffer[BufferSize];
// int in = 0;
// int out = 0;

// void *producer(void *pno)
// {
// 	int item;
// 	for (int i = 0; i < MaxItems; i++)
// 	{
// 		item = rand();
// 		sem_wait(&empty); //--
// 		pthread_mutex_lock(&mutex);
// 		buffer[in] = item;
// 		printf("Producer %d: Insert Item %d at %d\n", *((int *)pno), buffer[in], in);
// 		in = (in + 1) % BufferSize;
// 		pthread_mutex_unlock(&mutex);
// 		sem_post(&full); //++
// 	}
// 	return NULL;
// }

// void *consumer(void *cno)
// {
// 	for (int i = 0; i < MaxItems; i++)
// 	{
// 		sem_wait(&full);
// 		pthread_mutex_lock(&mutex);
// 		int item = buffer[out];
// 		printf("Consumer %d: Remove Item %d from %d\n", *((int *)cno), item, out);
// 		out = (out + 1) % BufferSize;
// 		pthread_mutex_unlock(&mutex);
// 		sem_post(&empty);
// 	}
// 	return NULL;
// }

// int main()
// {

// 	pthread_mutex_init(&mutex, NULL);
// 	sem_init(&empty, 0, 5);
// 	sem_init(&full, 0, 0);
// 	pthread_t prod[5], cons[5];
// 	int arr[5] = {1, 2, 3, 4, 5};

// 	for (int i = 0; i < MaxItems; i++)
// 	{
// 		pthread_create(&prod[i], NULL, producer, &arr[i]);
// 	}
// 	for (int i = 0; i < MaxItems; i++)
// 	{
// 		pthread_create(&cons[i], NULL, consumer, &arr[i]);
// 	}
// 	for (int i = 0; i < MaxItems; i++)
// 	{
// 		pthread_join(prod[i], NULL);
// 	}
// 	for (int i = 0; i < MaxItems; i++)
// 	{
// 		pthread_join(cons[i], NULL);
// 	}
// 	pthread_mutex_destroy(&mutex);
// 	sem_destroy(&full);
// 	sem_destroy(&empty);
// }
