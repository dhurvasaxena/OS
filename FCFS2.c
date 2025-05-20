#include <stdio.h>


struct Process {
    int pid, arrival, burst, completion, turnaround, waiting;
};

void sortByArrival(struct Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrival > p[j + 1].arrival) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}


void calculateFCFS(struct Process p[], int n) {
    int currentTime = 0;
    float totalTAT = 0, totalWT = 0;

    for (int i = 0; i < n; i++) {
        if (currentTime < p[i].arrival) {
            currentTime = p[i].arrival;  
        }
        p[i].completion = currentTime + p[i].burst;
        p[i].turnaround = p[i].completion - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;
        currentTime = p[i].completion;  

        totalTAT += p[i].turnaround;
        totalWT += p[i].waiting;
    }

    
    printf("\nPID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].arrival, p[i].burst, 
               p[i].completion, p[i].turnaround, p[i].waiting);
    }

    printf("\nAverage Turnaround Time: %.2f", totalTAT / n);
    printf("\nAverage Waiting Time: %.2f\n", totalWT / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Process %d (AT BT): ", i + 1);
        scanf("%d %d", &p[i].arrival, &p[i].burst);
    }

    sortByArrival(p, n);
    calculateFCFS(p, n);

    return 0;
}
