#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

/*

   This program illustrates the use of getpid() and getppid()
*/

int main()
{
    pid_t child1_pid, child2_pid, child3_pid, child1_1_pid;
    int i;
    int status = 0;
    pid_t parent;

    child1_pid = fork();
    if (child1_pid < 0)
    {
       perror("fork()");
       printf("main function: errno number is %d\n",errno);
       exit(child1_pid);
    }

    if (child1_pid > 0)
    {	 
	printf("From parent Process %d: child_1 is created with PID %d\n",getppid(), child1_pid);
        child2_pid = fork();
	//created child 2
	if(child2_pid > 0)
	{
		printf("From parent Process %d: child_2 is created with PID %d\n", getppid(), child2_pid);
		printf("From parent Process %d: Waiting for child_2 to complete before creating child_3\n",getppid());
	//wait for child 2 to complete before moving to child3
	wait(NULL);
	child3_pid = fork();

	//if parent, print out the pid of child3
	if(child3_pid > 0)
	{
		printf("From parent Process %d: child_3 is created with PID %d\n",getppid(), child3_pid);
	}

	//if child start executing B.out program
	if(child3_pid == 0)
	{
		printf("From child_3: Calling an external program B.out and leaving child_3...\n");
		execl("B.out","B.out",NULL);

	}
	}
    }
	//for child_1 to make a child.
    else  /*child*/
    {
	//create from child 1 child1.1
	child1_1_pid = fork();
		printf("From child_1: child_1.1 is created with PID %d\n",child1_1_pid);
	if(child1_1_pid < 0)
	{
		perror("fork()");
		printf("main function: errno number is %d\n", errno);
		exit(child1_1_pid);
	}
	
		
    }

     return 0;
}

