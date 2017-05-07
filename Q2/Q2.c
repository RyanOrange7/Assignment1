#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <error.h>
#include <stdlib.h>

int main(int argc, char** argv)
{

/*Initializing variables for fork*/
	int x, y, temp, fd[2], status1, status2;
	pid_t child;
	char line[80];
		
/*fork off a child*/
	child = fork();	
	if(child < 0)
	{
		perror("fork error");
		exit(-1);
	}
/*Parent process*/ 
	if (child > 0)
	{
		printf("From Parent %d: child with PID %d is created\n", getpid(), getpid());
		printf("From Parent %d: Reading X from the user:\n", getpid());
		scanf("%d", &x);
/*create the pipe*/
		if(pipe(fd) < 0)
		{
			perror("pipe error");
			exit(-1);
		}
		printf("A pipe was created for communication between parent and child\n");


		/* Writing to the pipe from Parent*/
		printf("From Parent %d: Writing X into the pipe\n", getpid());
		close(fd[0]);
		write(fd[1], "%d\n", x);
		wait(NULL);

/* Reading Y from the pipe as Parent*/
		printf("From Parent %d: The value of Y is %d\n", getpid(), temp);
		temp =  read(fd[0], line, 80);
		printf("From parent %d: The value of Y is %d\n", getpid(), temp);
		
	}

/*Child Process*/
	else
	{

		printf("From Child: Reading Y from the user:\n");
		scanf("%d", &y);
		sleep(5);
	
/* Reading and Writing from Pipe as Child*/
		printf("From Child: Writing Y into the pipe\n"); 
		temp = read(fd[1], line, 80);
		close(fd[1]);
		write(fd[0], "%d\n", y);
		printf("From child: The value of X is %d\n", temp);
	}

return 0;
}
