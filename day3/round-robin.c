#include <stdio.h>
#include <stdlib.h>
main()
{
    int bt[6], wt[6] = {0}, tat[6] = {0};
    float twt, ttat;
    int rt[6];
    int temp, j, ts, t = 0, x = 0;
    int count, i;
    system("clear");
    printf("\nEnter the count:");
    scanf("%d", &count);
    printf("\nEnter the Burst times:");
    for (i = 0; i < count; i++)
    {
        printf("\np[%d]:\t", i);
        scanf("%d", &bt[i]);
    }
    printf("\nEnter time slice :");
    scanf("%d", &ts);
    for (i = 0; i < count; i++)
        rt[i] = bt[i];
    while (1)
    {
        for (i = 0; i < count; i++)
        {
            if (rt[i] > 0)
            {
                if (rt[i] > ts)
                {
                    t += ts;
                    rt[i] -= ts;
                }
                else
                {
                    t += rt[i];
                    rt[i] = 0;
                    tat[i] = t;
                    wt[i] = t - bt[i];
                    x++;
                }
            }
        }
        if (x == count)
            break;
    }
    for (i = 0; i < count; i++)
    {
        twt += wt[i];
        ttat += tat[i];
    }

    printf("\npid \tBT \t TAT \t WT \n");
    for (i = 0; i < count; i++)
        printf("\n %d \t %d \t %d \t %d", i, bt[i], tat[i], wt[i]);
    printf("\nThe avg  waiting time is %f", twt / count);
    printf("\nThe avg turn around time is %f\n", ttat / count);
}
