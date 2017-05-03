#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*	
	Write a program in which the parent creates exactly 1 child process. The child process should print its 
	pid to the standard output and then finish. The parent process waits until it is sure that the child has 
	terminated. For this students are required to check in the man page of fork to see whether a parent is notified 
	of child termination via any signal. The parent terminates after it has waited for the child process.
*/

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
		printf("I am the child: %d\n", getpid());
		exit(0);
	}
	else
	{
			printf("Waiting for child to execute...\n");
			waitpid(pid, NULL, 2);
			printf("A child witd %d has been created!\n", pid);
	}	
	
	return EXIT_SUCCESS;
}


/*
	Output:
	
	Waiting for children to execute...
	I am the child: 12102
	A child witd 12102 has been created!
	
*/
