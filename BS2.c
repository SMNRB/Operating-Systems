#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char* argv[])
{

	pid_t pid;
	
	for(int i = 1; i < 17; i++)
	{
		pid = fork();
		
		if(pid < 0)
		{
			perror("Execvp error");
		}
	
		if(pid == 0)
		{
			printf("[%d] I am the child: %d\n", i, getpid());
			exit(0);
		}
		else
		{
			printf("Waiting for childs to execute...\n");
			wait(NULL);
		}	
	}
	
	printf("All 16 childs have been created!\n");
	
	/* The order is always "Waiting" then "child" and this 16 times, where as the child process prints its ID which is increased 
		by one every time it gets printed on the terminal. */
		
	/* I think the order of the messages can be preticted. */
	
	/* It think it depends on the OS */
	
	return EXIT_SUCCESS;
}
