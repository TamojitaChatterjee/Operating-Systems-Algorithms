//shortest seek time first
#include<stdio.h>
#include<stdlib.h>

int main(){
    /*
    n --> number of requests
    head --> current position of disks
    total --> total head movement
    */
    int n, head, total=0;

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    /*
    requests[] --> stores request positions
    completed[] --> keeps track of which requests are done
    completed[i] --> mark all requests as not served yet
    */
    int requests[n], completed[n];
    for(int i=0; i<n; i++){
        printf("Enter request %d: ", i+1);
        scanf("%d", &requests[i]);
        completed[i] = 0; //mark all as unvisited
    }

    printf("Enter head position: ");
    scanf("%d",&head);

    printf("\nOrder of serving requests:\n");
    /*
    loop through all requests and fill the one nearest to the head
    we ignore the already completed ones
    */
    for(int i=0; i<n; i++){ //this is run n times because we have to serve all n requests
        int shortest = -1; //index of closest request --> we don't know it yet
        int min_distance = 9999; //a big number which will be reduced later as any distance will be smaller than this

        for (int j=0; j<n; j++){ //we go throigh each and every request to check for completion
            if(!completed[j]){ //this is 0 if it is not served yet, !completed[j] means request hasn't been done yet
                int distance = abs(head - requests[j]); //this gives us the positive difference between current head and this request
                if(distance < min_distance){ //if this is the closest one yet
                    min_distance = distance; //save the distance as min_distance
                    shortest = j; //save the request's position as shortest
                }
            }
        }

        //serve the chosen request
        /*
        print the request
        add distance to total
        move the head to this request
        mark as completed
        */
        printf("%d -> ", requests[shortest]); //print the request we are about to serve
        total += abs(head - requests[shortest]); //add how far the head had to move to get there
        head = requests[shortest]; //move head to new position
        completed[shortest] = 1; //mark as completed
    }

    printf("End\n");
    printf("Total number of head movements: %d \n", total);

    return 0;
}