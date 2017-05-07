#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <error.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
/*variables for use in creating pipe and fork*/
	int fd[2];		//hold file dest of both ends of pipe
	pid_t grep_child;	//creating child pid for grep
	int status1, status2;	//status for execl functions
/*create the pipe*/
	printf("1");
	if(pipe(fd) < 0)
	{
		perror("pipe error");
		exit(1);
	}		
/*fork off a child*/
	grep_child = fork();	
	if(grep_child < 0)
	{
		perror("fork error");
		exit(1);
	}

/*Parent process*/ 
	if (grep_child > 0)
	{
		printf("Parent %d", getppid());
		close(fd[0]);
		if(dup2(fd[1],STDOUT_FILENO)<0)
		{
			perror("can't dup");
			exit(1);
		}	
		status1 = execlp("ls","ls","-l",NULL);
		if(status1 < 0)
		{
		perror("parent: exec problem");
		exit(1);
		}
	wait(NULL);
	}

/*Child process*/
	else 
	{
		printf("Child %d", getpid());
		close(fd[1]);
		if(dup2(fd[0],STDIN_FILENO)<0)
		{
			perror("can1't dup");
			exit(1);
		}	
		status2 = execlp("grep","grep", "xxxx",NULL);
		if(status2 < 0)
		{
			perror("child: exec problem");
			exit(1);
		}

	}
	return(0);

}
