//scan --> disk scheduling algorithm
#include<stdio.h>
#include<stdlib.h>

//bubble sort to arrange requests
void sort(int arr[], int n){
    for (int i=0; i<n-1; i++){
        for (int j=0; i<n-i-1; i++){
            if (arr[j]>arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main(){

    /*
    requests[] --> array to store disk requests
    n --> number of requests
    head --> current disk position
    total --> total movement
    direction --> direction of head movement first
    */
    int requests[1000], n, head, total=0;
    char direction;

    printf("Enter number of disk requests: ");
    scanf("%d",&n);

    printf("Enter disk requests:");
    for(int i=0; i<n; i++){
        scanf("%d", &requests[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d",&head);

    printf("Enter direction (L for Left, R for Right): ");
    scanf(" %c",&direction);

    //add head to requests to help with splitting
    requests[n] = head;
    n++;

    //bubble sort the requests
    //we include the current head so that we know where to start from
    sort(requests, n);

    //finding the head in the sorted array
    int index;
    for(int i=0; i<n; i++){
        if (requests[i] == head){
            index = i;
        }
    }

    printf("Seek sequence: ");

    if (direction == 'R' || direction == 'r'){
        //right side
        for (int i = index; i<n; i++){
            printf("%d ->", requests[i]);
            total += abs(head - requests[i]);
            head = requests[i];
        }

        //then reverse and go left
        for (int i = index-1; i>= 0; i--){
            printf("%d -> ", requests[i]);
            total += abs(head - requests[i]);
            head = requests[i];
        }
    }else{
        //move left first
        for(int i = index; i>=0; i--){
            printf("%d -> ", requests[i]);
            total += abs(head-requests[i]);
            head = requests[i];
        }

        //go to the start
        if(head!=0){
            total += abs(head - 0);
            head = 0;
        }

        //then reverse and go right
        for(int i = index+1; i<n; i++){
            printf("%d -> ", requests[i]);
            head = requests[i];
        }
    }

    printf("\nTotal head movement = %d\n", total);

    return 0;
}