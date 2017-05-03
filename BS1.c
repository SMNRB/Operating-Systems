#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char* argv[])
{

	pid_t pid;	// signed integer for process id
	
	for(int i = 1; i < 10; i++)
	{
		pid = fork();
		
		if(pid < 0)
		{
			perror("Execvp error");
		}
	
		if(pid == 0)
		{
			exit(0);
		}
		else
		{
			wait(NULL);
		}	
	}
	
	return EXIT_SUCCESS;
}
