#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>


int main(void)
{

	pid_t pid;
	int fd[2];
	char buffer[80];
	char my_string[] = "Hello there!\n";
	
	pipe(fd);
	pid = fork();
	
	if(pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if(pid == 0)
	{
		/* Child Process */
		close(fd[0]);
		write(fd[1], my_string, (strlen(my_string) + 1));
		exit(EXIT_SUCCESS);
	}
	else
	{
		/* Parent Process */
		close(fd[1]);
		while(read(fd[0], buffer, sizeof(buffer)) > 0)
		{
			printf("Received String: %s", buffer);
		}
	}
        
	return EXIT_SUCCESS;
}
