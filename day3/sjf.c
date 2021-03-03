#include <stdio.h>
#include <stdbool.h>
struct Process
{
    int pid; // process ID
    int bt;  // burst Time
};
int qsort();


void findWaitingTime(struct Process process[], int count, int *wt)
{
    wt[0] = 0;
    for (int i = 1; i < count; i++)
    {
        wt[i] = wt[i - 1] + process[i-1].bt;
    }
}
void findTurnAroundTime(struct Process process[], int count, int *wt, int *tat)
{
    for (int i = 0; i < count; i++)
    {
        *(tat + i) = process[i].bt + wt[i];
    }
}
void findavgTime(struct Process process[], int count)
{
    int wt[count], tat[count], total_wt = 0, total_tat = 0;

    findWaitingTime(process, count, wt);
    findTurnAroundTime(process, count, wt, tat);

	printf("Processes \t Burst time \t Waiting time \t Turn around time\n"); 

for(int i=0;i<count;i++){
    total_tat+=tat[i];
    total_wt+=wt[i];
    printf("%d\t",process[i].pid); 
		printf("%d\t", process[i].bt ); 
		printf("%d\t",wt[i] ); 
		printf("%d\n",tat[i] );
}
printf("total waiting time :%lf \n",(double)(total_wt/count));

printf("total waiting time :%lf",(double)((double)total_tat/(double)count));


}

int comparison(void *a, void *b)
{
       struct Process *process1 = a;
     struct Process *process2 = b;
     return (process1->bt)-(process2->bt);
}
int main()
{
    struct Process proc[] = {{1, 21}, {2, 3}, {3, 6}, {4, 2}};
    int n = sizeof proc / sizeof proc[0];

    // sorting processes by burst time.
    qsort(proc, 4, sizeof(struct Process), comparison);
    
    findavgTime(proc, n);


    return 0;
}