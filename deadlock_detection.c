#include <stdio.h>
#define MAX 10

int n; // number of processes
int wfg[MAX][MAX]; // wait-for graph (adjacency matrix)
int visited[MAX] = {0}; // visited array for DFS
int recStack[MAX] = {0}; // recursion stack to detect cycles

// DFS function to detect cycles
int dfs(int i) {
    visited[i] = 1;
    recStack[i] = 1;

    for (int j = 0; j < n; j++) {
        if (wfg[i][j]) {
            if (!visited[j] && dfs(j)) {
                return 1; // cycle found
            }
            else if (recStack[j]) {
                return 1; // back edge found, cycle
            }
        }
    }

    recStack[i] = 0; // remove from recursion stack before backtracking
    return 0; // no cycle
}

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter wait-for graph (Adjacency Matrix):\n");
    printf("Enter 1 if process i is waiting for process j, else 0\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &wfg[i][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (dfs(i)) {
                printf("Deadlock detected!\n");
                return 0;
            }
        }
    }

    printf("No deadlock detected. System is safe.\n");
    return 0;
}