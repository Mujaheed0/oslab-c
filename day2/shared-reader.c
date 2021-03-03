
// Program to demonstrate basic operations on shared memory--reader


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() 
{ 
	// ftok to generate unique key 
	key_t key = ftok("shmfile",65); 

	// shmget returns an identifier in shmid 
	int shmid = shmget(key,1024,0666|IPC_CREAT); 

	// shmat to attach to shared memory 
	int *str = (int *) shmat(shmid,(void*)0,0); 
    printf("%p",str);
    for(int i=0;str[i]!=0;i++)
        printf("\n MP: data value - [%d] is at location [%u] \n", *(str+i),(str+i));

	
	//detach from shared memory 
	shmdt(str); 
	
	// destroy the shared memory 
	shmctl(shmid,IPC_RMID,NULL); 
	
	return 0; 
} 
