#include "header.h"

typedef struct
{
	int allocations; /* Number of allocations */
	int size; /* Size of allocation in bytes */
} memory_parameters;

void Usage() 
{
	printf("ERROR\n");
	printf("USAGE ./membench <Threads> <Allocations> <Size>\n");
}

void* allocate_memory(int size)
{
	return malloc(size);
}

void deallocate_memory(void* memory) 
{
	free(memory);
}

void* threads_exe(void* arg)
{
	memory_parameters memp = *(memory_parameters*)arg;
	//void* temp_memory = allocate_memory(memp.size);
	
	for(int i = 0; i < memp.allocations; i++)
	{
		//printf("(%d %d)", i, memp.size);
		void* temp_memory = allocate_memory(memp.size);
		pthread_cleanup_push(deallocate_memory, temp_memory);
		pthread_cleanup_pop(1);
	}
	
	/* Register a cleanup handler for this buffer, to deallocate it in case the thread exits or is cancelled.  */
	//pthread_cleanup_push(deallocate_memory, temp_memory);
	
	/* Exit current Thread */
	//pthread_t tid = pthread_self();
	//pthread_exit(&tid);
	
	/* Unregister the cleanup handler.  Because we pass a nonzero value,this actually performs the cleanup by callingdeallocate_buffer.  */
	//pthread_cleanup_pop(1);
	
	return NULL;
}


int main(int argc, char* argv[])
{
	
	if(argc < 4)
	{
		Usage();
		exit(EXIT_FAILURE);
	}
	
	int array[3];
	
	for(int i = 0; i < argc - 1; i++)
	{
		if (sscanf (argv[i + 1], "%i", &array[i]) != 1) 
		{
			fprintf(stderr, "error - not an integer");
		}
	}
	
	pthread_t tid[array[0]];
	memory_parameters mp;
	mp.allocations = array[1];
	mp.size = array[2];

	for(int i = 0; i < array[0];  i++)
	{
		if(pthread_create(&tid[i], NULL, threads_exe, &mp))
		{
			perror("pthread_create");
			exit(EXIT_FAILURE);
		}
		
	}

	for(int i = 0; i < array[0]; i++)
	{
		if(pthread_join(tid[i], NULL))
        {
        	perror("pthread_join");
        	exit(EXIT_FAILURE);
        }
	}
	
	return EXIT_SUCCESS;
}

// valgrind --leak-check=yes ./m 10 10 10
