#include <stdio.h>

#define p 5 // number of processes
#define r 3 // number of resources

int main() {
    int alloc[p][r] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    int max[p][r] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    int avail[r] = {3, 3, 2};

    int need[p][r]; // Remaining needs = max - alloc
    int finish[p] = {0}; // Tracks if process is done
    int safe[p]; // Stores safe sequence

    // Step 1: Calculate need matrix
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    int count = 0; // Number of finished processes

    // Step 2: Find safe sequence
    while (count < p) {
        int found = 0;

        for (int j = 0; j < p; j++) {
            if (!finish[j]) {
                int canRun = 1;

                // Check if this process can run
                for (int k = 0; k < r; k++) {
                    if (need[j][k] > avail[k]) {
                        canRun = 0;
                        break;
                    }
                }

                // If it can run, simulate it finishing
                if (canRun) {
                    for (int k = 0; k < r; k++) {
                        avail[k] += alloc[j][k]; // Release its resources
                    }
                    safe[count++] = j;
                    finish[j] = 1;
                    found = 1;
                }
            }
        }

        // If no process could run in this pass, deadlock
        if (!found) {
            printf("System NOT in safe state\n");
            return 0;
        }
    }

    // Step 3: Print the safe sequence
    printf("System is in safe state.\nSafe Sequence is: ");
    for (int i = 0; i < p; i++) {
        printf("P%d ", safe[i]);
    }
    printf("\n");

    return 0;
}