#include <stdio.h>


void findWaitingTime(int *processes, int count, int *burst_time, int *wt)
{
    wt[0] = 0;
    for (int i = 1; i < count; i++)
    {
        wt[i] = wt[i - 1] + burst_time[i - 1];
    }
}
void findTurnAroundTime(int *processes, int count, int *wt, int *burst_time, int *tat)
{
    for (int i = 0; i < count; i++)
    {
        *(tat + i) = burst_time[i] + wt[i];
    }
}
void findavgTime(int *processes, int count, int *burst_time)
{
    int wt[count], tat[count], total_wt = 0, total_tat = 0;

    findWaitingTime(processes, count, burst_time, wt);
    findTurnAroundTime(processes, count, wt, burst_time, tat);

	printf("Processes \t Burst time \t Waiting time \t Turn around time\n"); 

for(int i=0;i<count;i++){
    total_tat+=tat[i];
    total_wt+=wt[i];
    printf("%d\t",(i+1)); 
		printf("%d\t", burst_time[i] ); 
		printf("%d\t",wt[i] ); 
		printf("%d\n",tat[i] );
}
printf("total waiting time :%lf \n",(double)(total_wt/count));

printf("total waiting time :%lf",(double)((double)total_tat/(double)count));


}

int main()
{
    int processes[] = {1, 2, 3};
    int n = sizeof(processes) / sizeof(processes[0]);
    int burst_time[] = {24, 3, 4};
    findavgTime(processes, n, burst_time);
    return 0;
}