#include <stdio.h>
#include <stdbool.h>

int main() {
    int n = 5; // Number of processes
    int m = 3; // Number of resource types
    // Allocation Matrix
    int alloc[5][3] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    // Maximum Matrix
    int max[5][3] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    // Available Resources
    int avail[3] = {3, 3, 2};

    // Request (from process P1 in this example)
    int req_process = 1;
    int request[3] = {1, 0, 2};

    int need[5][3], i, j, k;

    // Calculate Need Matrix
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    // Step 1: Check if request <= need
    bool validRequest = true;
    for (j = 0; j < m; j++) {
        if (request[j] > need[req_process][j]) {
            validRequest = false;
            break;
        }
    }

    if (!validRequest) {
        printf("Error: Process has exceeded its maximum claim.\n");
        return 0;
    }

    // Step 2: Check if request <= available
    for (j = 0; j < m; j++) {
        if (request[j] > avail[j]) {
            printf("Resources are not available. Process P%d must wait.\n", req_process);
            return 0;
        }
    }

    // Step 3: Pretend to allocate the resources
    for (j = 0; j < m; j++) {
        avail[j] -= request[j];
        alloc[req_process][j] += request[j];
        need[req_process][j] -= request[j];
    }

    // Step 4: Safety Check using Banker's Algorithm
    int finish[5] = {0}, safeSequence[5];
    int count = 0;
    int temp_avail[3];

    for (j = 0; j < m; j++)
        temp_avail[j] = avail[j];

    while (count < n) {
        bool found = false;
        for (i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canRun = true;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > temp_avail[j]) {
                        canRun = false;
                        break;
                    }
                }

                if (canRun) {
                    for (k = 0; k < m; k++)
                        temp_avail[k] += alloc[i][k];
                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = true;
                }
            }
        }

        if (!found) {
            printf("Request cannot be granted immediately as it leads to an unsafe state.\n");
            return 0;
        }
    }

    printf("Request can be granted.\nSystem is in a SAFE state.\nSafe sequence is: ");
    for (i = 0; i < n; i++)
        printf("P%d ", safeSequence[i]);
    printf("\n");

    return 0;
}
