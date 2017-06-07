#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/file.h>
#include <stdbool.h>
#include "queue.h"

#define THREAD_AMOUNT 4
pthread_mutex_t lock;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* create_file(void* arg)
{
	int local_sum = 0;
	int temp = 0;
	queue* my_queue = *(queue**)arg;
	
	if(queue_size(my_queue) < 100000) {sleep(1);}
	
	
	while(true)
	{			
		pthread_mutex_lock(&lock);	
		
			pthread_cond_wait(&cond, &lock);
			
			if((temp = queue_dequeue(my_queue)) == 0)
			{
				printf("Thread sum: %d\n", local_sum);
				pthread_mutex_unlock(&lock);
				pthread_cond_signal(&cond);
				//pthread_exit(NULL);
				break;
			}
			else
			{
				local_sum += temp;
				pthread_mutex_unlock(&lock);
				pthread_cond_signal(&cond);
			}
	}
	
	printf("Finished Thread sum: %d\n", local_sum);
	pthread_exit(NULL);
	
	return NULL;
}


int main(void) {
    
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);
    pthread_t tid[THREAD_AMOUNT];
    queue* my_queue = queue_create();

    for(int i = 0; i < THREAD_AMOUNT; i++)
    {
        if(pthread_create(&tid[i], NULL, create_file, &my_queue))
        {
        	perror("pthread_create");
        	exit(EXIT_FAILURE);
        }
    }
    
    for(int j = 0; j < 100000; j++)
    {
    	queue_enqueue(my_queue, 1);
    }
    
    for(int k = 0; k < 4; k++)
    {
    	queue_enqueue(my_queue, 0);
    }
    
    sleep(9);
    
    pthread_cond_signal(&cond);
    
    printf("Queue-size: %d\n", queue_size(my_queue));
    
    for(int h = 0; h < THREAD_AMOUNT; h++)
    {      
        if(pthread_join(tid[h], NULL))
        {
        	perror("pthread_join");
        	exit(EXIT_FAILURE);
        }
    }
    
	printf("Queue-size: %d\n", queue_size(my_queue));
	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&cond);
    	
    return EXIT_SUCCESS;
}
