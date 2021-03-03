#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int getpid();
void* square(void *a1)
{
    int *a = a1;
    printf("\n THRT:Thread task \t thread id is %lu", pthread_self());
    system("ps -l");
    printf("\n THRT: PID = %d \n", getpid());
    printf("\n squrare of %d is %d \n", *a, (*a * *a));
}
int main()
{
    pthread_t thr_id;
    int rval, number, i;
    system("clear");
    printf(" enter the number to square:\t");
    scanf("%d", &number);
    printf("\n MainThread: Sizeof pthread_t is %lu \n",
           sizeof(pthread_t));
    rval = pthread_create(&thr_id, NULL, &square, &number);
    printf("\n MainThread: rval = %d \n", rval);
    printf("\n MainThread: Thread id = %lu \t process id = %d\n",
           pthread_self(), getpid());
    if (rval == -1)
    {
        perror("THRD-CR-ERR:");
        exit(1);
    }
    rval = pthread_join(thr_id, NULL);
}