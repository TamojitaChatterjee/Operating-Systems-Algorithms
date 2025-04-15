//c-scan --> disk scheduling
#include<stdio.h>
#include<stdlib.h>

#define MAX 100

//bubble sort
void sort(int arr[], int n){
    for (int i = 0; i<n-1; i++){
        for (int j = 0; j<n-i-1; j++){
            if(arr[j]>arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main(){
    int requests[MAX], n, head, total = 0;
    int disk_size;
    char direction;

    printf("Enter number of disk requests: ");
    scanf("%d",&n);

    printf("Enter disk requests: ");
    for(int i = 0; i<n; i++){
        scanf("%d", &requests[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d",&head);

    printf("Enter total number of cylinders (disk size): ");
    scanf("%d",&disk_size);

    printf("Enter direction: ");
    scanf("%c",&direction);

    //add current head position to list and sort all
    requests[n] = head;
    n++;

    sort(requests, n);

    //find index of head in sorted array (head position)
    int index = 0;
    for (int i = 0; i< n; i++){
        if(requests[i] == head){
            index = i;
            break;
        }
    }

    printf("\nSeek Sequence\n");

    if(direction == 'R' || direction == 'r'){
        //move right from head to end
        for (int i = 0; i<n; i++){
            printf("%d -> ", requests[i]);
            total += abs(head - requests[i]);
            head = requests[i];
        }

        //jump to the beginning
        if(head != disk_size - 1){
            total += abs((disk_size -1) - head);
            head = 0;
            total += head;
            printf("0 ->");
        }

        //continue from beginning
        for (int i = 0; i< index; i++){
            printf("%d ->", requests[i]);
            total += abs(head - requests[i]);
            head = requests[i];
        }
    }else if (direction == 'L' || direction == 'l'){
        //move from left to start
        for(int i = index; i< n; i--){
            printf("%d ->", requests[i]);
            total += abs(head - requests[i]);
            head = requests[i];
        }

        //jump to end
        if (head != 0){
            total += head;
            head = disk_size - 1;
            total += disk_size - 1;
            printf("%d -> ", disk_size - 1);
        }

        //continue to right
        for (int i = n-1; i>index; i--){
            printf("%d -> ", requests[i]);
            total += abs(head - requests[i]);
            head = requests[i];
        }
    }else{
        printf("Invalid input. Use 'L' or 'R' \n ");
        return 1;
    }

    printf("\nTotal Head movement = %d\n", total);
    return 0;
}