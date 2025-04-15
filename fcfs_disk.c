#include<stdio.h>
#include<stdlib.h>

int main(){
    /*
    n --> how many disks will the user enter
    head --> current position of the disks's read/write arm
    total --> keeps track of the total distance moved by the head
    */
    int n, head, total = 0;

    printf("Enter number of disk requests: ");
    scanf("%d",&n);

    int requests[n];

    printf("Enter the disk requests: \n");
    for(int i=0; i<n; i++){
        scanf("%d",&requests[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d",&head);
    /*
    loop through all disk requests
    for each request:
        - print it
        - calculate the abstract value of the head movement
        - add it to total
        - update the new position of the head
    */
    printf("\nOrder of serving requests:\n");
    for(int i=0; i<n; i++){
        printf("%d -> ", requests[i]);
        total += abs(requests[i] - head);
        head = requests[i];
    }

    printf("End\n");
    printf("Total head movement: %d\n", total);
    return 0;
}