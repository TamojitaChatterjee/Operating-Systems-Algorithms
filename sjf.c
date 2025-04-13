#include <stdio.h>

int main() {

    //initializing all variables
    /*
    n --> number of processes
    pid --> process ID
    at --> arrival time
    bt --> burst time
    ct --> completion time
    tat --> turnaround time
    wt --> waiting time
    rt --> response time
    */

    int n;
    int pid[10], at[10], bt[10], ct[10] = {0}, tat[10] = {0}, wt[10] = {0}, rt[10] = {0};
    int completed[10] = {0};

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter process id, arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d %d", &pid[i], &at[i], &bt[i]);
    }

    /*
    current time is the time as the system completes processes that are being schedules and executed
    total completed keeps a track of how many processes have been executed till now
    */
    int current_time = 0, total_completed = 0;

    while (total_completed < n) {
        int min_index = -1;
        int min_burst_time = 9999;

        for (int i = 0; i < n; i++) {
            if (at[i] <= current_time && !completed[i] && bt[i] < min_burst_time) {
                min_burst_time = bt[i];
                min_index = i;
            }
        }
        
        /*
        The formulae used are:
        ct = at+bt
        tat = ct-at
        wt = tat-bt
        rt = wt
        */

        if (min_index == -1) {
            current_time++;
        } else {
            wt[min_index] = current_time - at[min_index];
            current_time += bt[min_index];
            ct[min_index] = current_time;
            tat[min_index] = ct[min_index] - at[min_index];
            rt[min_index] = wt[min_index];
            completed[min_index] = 1;
            total_completed++;
        }
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
    }

    return 0;
}