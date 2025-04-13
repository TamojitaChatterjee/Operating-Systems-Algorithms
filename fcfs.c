//first come first serve scheduling algorithm
#include <stdio.h>

int main() {
    int n;

    /*
    pid --> process ID
    arr_time --> arrival time
    wait_time --> waiting time
    burst_time --> burst time
    tat --> turnaround time
    completion_time --> completion time/finish time
    response_time --> response time
    */

    int pid[10], arr_time[10], wait_time[10], burst_time[10], tat[10], completion_time[10], response_time[10];
    float avg_wait_time = 0, avg_tat = 0, avg_response_time = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter process ID, arrival time, and burst time for process %d: ", i + 1);
        scanf("%d %d %d", &pid[i], &arr_time[i], &burst_time[i]);
    }

    /*
    The formulae used here are:
    completion time = arrival time + burst time
    turnaround time = completion time - arrival time
    waiting time = turnaround time - burst time
    response time = first response - arrival time
    Here, since the given algorithm is non-preemptive, waiting time = response time
    */

    // First process
    wait_time[0] = 0;
    completion_time[0] = arr_time[0] + burst_time[0];
    tat[0] = completion_time[0] - arr_time[0];
    response_time[0] = wait_time[0];

    // Remaining processes
    for (int i = 1; i < n; i++) {
        int start_time = completion_time[i - 1];
        if (start_time < arr_time[i]) {
            start_time = arr_time[i];
        }
        wait_time[i] = start_time - arr_time[i];
        completion_time[i] = start_time + burst_time[i];
        tat[i] = completion_time[i] - arr_time[i];
        response_time[i] = wait_time[i];
    }

    // Print results
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\tResponse Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", pid[i], arr_time[i], burst_time[i], completion_time[i], tat[i], wait_time[i], response_time[i]);
        avg_wait_time += wait_time[i];
        avg_tat += tat[i];
        avg_response_time += response_time[i];
    }

    // Calculate and print averages
    avg_wait_time /= n;
    avg_tat /= n;
    avg_response_time /= n;

    printf("\nAverage Waiting Time: %.2f\n", avg_wait_time);
    printf("Average Turnaround Time: %.2f\n", avg_tat);
    printf("Average Response Time: %.2f\n", avg_response_time);

    return 0;
}