#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/file.h>

#define THREAD_AMOUNT 10

void* create_file(void* arg)
{
	int random = rand() % 2;
    sleep(random);

	int number = *(int*)arg;
	char filename[10];
	
	snprintf(filename, sizeof(filename), "thread%d", number);
	FILE *file;

	if((file = fopen(filename, "w")) == NULL)
	{
		perror("fopen");
		exit(EXIT_FAILURE);
	}
	
	int tid = pthread_self();
	
	// File operations are already thread safe, so there is no need for more portection
	if(fprintf(file, "%d", tid) == -1)
	{
		perror("fprintf");
		exit(EXIT_FAILURE);
	}
	fclose(file);
	
	return NULL;
}

int one_or_zero()
{
	int number = rand() % 2;
	return number;
}


int main(void) {

    srand(time(NULL));
    
    pthread_t tid[THREAD_AMOUNT];

    for(int i = 0; i < THREAD_AMOUNT; i++)
    {
        if(pthread_create(&tid[i], NULL, create_file, &i))
        {
        	perror("pthread_create");
        	exit(EXIT_FAILURE);
        }
        
        
        if(pthread_join(tid[i], NULL))
        {
        	perror("pthread_join");
        	exit(EXIT_FAILURE);
        }
        
        //pthread_detach(tid[i]);
        
    }
    
    for(int j = 0; j < THREAD_AMOUNT; j++)
    {
		if(one_or_zero() == 0)
		    {
		    	// cancel thread
		    	pthread_cancel(tid[j]);
		    	printf("Canceled thread %d\n", j);
		    }
	}
    
    for(int i = 0; i < 10; i++)
    {
    	pthread_exit(&tid[i]);
    }
    	
    return EXIT_SUCCESS;
}
