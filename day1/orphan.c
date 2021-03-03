#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	int pid;    

	system("clear");
	printf(" Process ID is %d \t Parent Process ID is 			%d\n\n",getpid(),getppid());

	system("ps -l");

	printf(" Program to demonstrate orphan process \n");

	pid = fork();
	if (pid == -1)
	{    perror("FRK-ERR:");
		exit(1);
	}

	if (pid == 0)
	{    printf(" CHLD-PR: Process ID is %d \t Parent   			Process ID is %d \n\n", getpid(),getppid());
			system("ps -l");
			sleep(2);
			printf(" CHLD-PR: Process ID is %d \t Parent 					Process ID is %d \n\n", getpid(),getppid());
			system("ps -l");
	}
	else  
	{    sleep(1);
		printf("\n PARNT-PR: Process ID is %d \t Parent 				Process ID is %d \n\n", getpid(),getppid());
		system("ps -l");
	}
}




