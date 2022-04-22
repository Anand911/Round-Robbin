#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
struct pcb
{
    int at, pno;
    int bt, tt, wt, ct, rem_bt, pos;
};
int test_flag(int flag[], int n)
{
    for (int i = 0; i < n; i++)
    {
        // printf("\nflag=%d",flag[i]);
        if (flag[i] == 0)
            return FALSE;
    }
    return TRUE;
}
void main()
{
    struct pcb p[10], k;
    int n, ct, i, j, flag[10], a, x, avgtt, avgwt, Current_time = 0;
    int TQ;
    printf("\nEnter no. of processes: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("\nEnter for process%d:", i + 1);
        printf("\nArival time:");
        scanf("%d", &p[i].at);
        printf("\nBurst time:");
        scanf("%d", &p[i].bt);
        p[i].pno = i + 1;
    }
    printf("\nEnter The Time Quantam:");
    scanf("%d", &TQ);

    for (i = 0; i < n; i++)
    {
        p[i].rem_bt = p[i].bt;
        flag[i] = 0;
        p[i].pos = 0;
    }
    // sorting at
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < (n - i) - 1; j++)
        {
            if (p[j].at > p[j + 1].at)
            {
                k = p[j + 1];
                p[j + 1] = p[j];
                p[j] = k;
            }
        }
    }
  
    p[0].pos = 1;
    i = 0;
    int curr_pos = 1, assign_pos = 1;
    avgtt = avgwt = 0;
    while (test_flag(flag, n) == FALSE)
    {
        
        if (p[i].rem_bt >= TQ) //if remaining time in more than time quantam
        {
            Current_time = Current_time + TQ; //add time quantam
            p[i].rem_bt -= TQ;
            if (p[i].rem_bt == 0)
            {
                p[i].ct = Current_time;
                flag[i] = 1;
            }
            ++curr_pos;
        }
        else
        {
            if(flag[i]==1)
                Current_time++;
            else{
            Current_time = Current_time + p[i].rem_bt;  ///else add remaining burst time
            p[i].ct = Current_time;
            p[i].rem_bt -= p[i].rem_bt;
            flag[i] = 1;
            ++curr_pos;
            }
            
        }
        for (j = 0; j < n; j++)
        {
            
            if ((Current_time >= p[j].at) && (p[j].pos == 0)) //check if any element has arrived during current time
            {                                                 //and with no position in read_queue was assigned
                p[j].pos = ++assign_pos;
            }
        }
        if (flag[i] != 1)
            p[i].pos = ++assign_pos;
        
        for (j = 0; j < n; j++)
        {
            if (curr_pos == p[j].pos)
                i = j;
        }
    }

    for (i = 0; i < n; i++)
    {
        p[i].tt = p[i].ct - p[i].at;
        avgtt = avgtt + p[i].tt;
        p[i].wt = p[i].tt - p[i].bt;
        avgwt = avgwt + p[i].wt;
    }
    printf("\nprocess no.\tAT\tBT\tCT\tTT\tWT");
    for (i = 0; i < n; i++)
    {
        printf("\n%d\t\t%d\t%d\t%d\t%d\t%d", p[i].pno,
               p[i].at, p[i].bt, p[i].ct, p[i].tt, p[i].wt);
    }
    printf("\n");
    printf("Avg TT=%d\nAvg WT=%d\n", avgtt / n, avgwt / n);
}
