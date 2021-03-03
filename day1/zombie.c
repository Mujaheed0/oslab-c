
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
	int pid, rval;

	system("clear");

	printf("\n Process ID is %d \t Parent Process ID is        %d\n\n",getpid(),getppid());
	system("ps -l");

	printf("\n Program to demonstrate zombie process \n");

	pid = fork();
	if (pid == -1)
	{
		perror("FRK-ERR:");
		exit(1);
	}

	if (pid == 0)
	{    printf("\n CHLD-PR: Process ID is %d \t Parent       Process ID is %d \n\n", getpid(),getppid());
		system("ps -l");
		exit(0);
	}
	else  
	{
		sleep(1);
		printf("\n PRNT-PR: Process ID is %d \t Parent              Process ID is %d \n\n", getpid(),getppid());
		system("ps -l");
		printf("\n\n PRNT-PR: Child ID - the value returned     by FORK function is %d \n",pid);
		rval =(int) wait(0);
		printf("\n PRNT-PR: Id of child process terminated       returned through WAIT function is %d \n",rval);
	}
}

