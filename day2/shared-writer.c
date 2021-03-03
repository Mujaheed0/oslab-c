
// Program to demonstrate basic operations on shared memory--writer


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>


int main()
{
    int shmid, *shmptr,nb,count,i;


    system("clear");

    printf("\n MP: PID = %d \t PPID = %d \n",getpid(),getppid());

    printf("\n program to demonstrate basic operations on shared memory \n");

    printf("\n enter the number of bytes of space required \t:");
    scanf("%d",&nb);
    
	key_t key = ftok("shmfile",65); 

	// shmget returns an identifier in shmid 
	 shmid = shmget(key,1024,0666|IPC_CREAT);


    if (shmid == -1)
    {
        perror("SHM-ERR:");
        exit(1);
    }

    printf("\n MP: SHM-ID is %u ",shmid);

    system("ipcs -m");

    shmptr = (int *)shmat(shmid,0,0);    
    if (shmptr ==     NULL)
    {
        perror("SHMAT-ERR:");
        exit(1);
    }

    printf("\n MP: SHM-ID is %u and shared memory pointer is %p",shmid,shmptr);
    system("ipcs -m");
    printf("\n enter the number of elements to insert \t");
    scanf("%d",&count);

    for (i=0;i< count;i++)
    {
        printf("\n enter the number to write to memory \t");
        scanf("%d",&shmptr[i]);
    }

    printf("\n The elements in shared memory are :\n");
    for(i=0;i<count;i++)
        printf("\n MP: data value - [%d] is at location [%p] \n", shmptr[i],&shmptr[i]);

    shmdt(shmptr);

    system("ipcs -m");
}

