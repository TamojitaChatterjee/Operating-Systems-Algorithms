//shortest remaining time first
#include<stdio.h>
#include<limits.h>
int main(){

    /*
    Initializing all variables
    n --> number of processes
    pid --> process ID
    at --> arrival time
    bt --> burst time
    ct --> completion time
    wt --> waiting time
    tat --> turnaround time
    rt --> remaining time
    */
    int n;
    int pid[10], at[10], bt[10], ct[10], wt[10], tat[10], rt[10];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(int i=0; i<n; i++){
        printf("Enter process ID, arrival time and burst time for process %d: ",i+1);
        scanf("%d %d %d", &pid[i], &at[i], &bt[i]);
        rt[i]=bt[i];
    }

    int time = 0, completed = 0;

    /*
    time --> current time on CPUs clock
    completed --> keeps track of number of processes completed
    */

    while(completed<n){
        int shortest = -1;
        int min_remaining = INT_MAX;

         /*
        shortest --> keeps track of which processes should be run next; it is storing the index of the process that has the shortest remaining time and has already arrived
        INT_MAX --> constant defined under <limits.h>; stands for maximum possible values int can hold -- sets a very large default value
        Here, we are using that so that we can update the value of min_remaining if we find a smaller value
        */

        for(int i=0; i<n; i++){
            if(at[i]<=time && rt[i]>0 && rt[i]<min_remaining){
                min_remaining = rt[i];
                shortest = i;
            }
        }

        /*
        Here we are checking:
        1. Has the process arrived? 
        2. Is it not finished?
        3. Is it shorter than what we have seen so far?
        If these three conditions are true, we apply 'shortest' to the process
        */

        //if no process is ready, move time forward
        if (shortest == -1){
            time++;
            continue;
        }

        //execute selected process for 1 unit of time
        rt[shortest]--;
        time++;

        //if process is completed
        if (rt[shortest] == 0){
            completed++;
            ct[shortest] = time;
            tat[shortest] = ct[shortest] - at[shortest]; //tat=ct-at
            wt[shortest] = tat[shortest] - bt[shortest]; //wt = tat - bt
        }
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i = 0; i<n; i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    return 0;
}