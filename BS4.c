#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char* argv[])
{

	pid_t pid;
	pid = fork();
		
	if(pid < 0)
	{
		perror("Execvp error");
	}
	
	if(pid == 0)
	{
		//while(1); // To check if wait(&pid) works 
		printf("I am the child: %d\n", getpid());
		exit(0);
	}
	else
	{
			printf("Waiting for children to execute...\n");
			waitpid(pid, NULL, 2);
			printf("A child witd %d has been created!\n", pid);
	}	
	
	return EXIT_SUCCESS;
}
