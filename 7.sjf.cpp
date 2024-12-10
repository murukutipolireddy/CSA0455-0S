#include <stdio.h>

#define MAX_PROCESSES 100

typedef struct {
    int id;            // Process ID
    int arrivalTime;   // Arrival Time
    int burstTime;     // Burst Time
    int waitingTime;   // Waiting Time
    int turnaroundTime; // Turnaround Time
    int isCompleted;   // Flag to check if the process is completed
} Process;

// Function to find the process with the shortest burst time that has arrived
int findShortestJob(Process processes[], int n, int currentTime) {
    int minBurstTime = __INT_MAX__;
    int index = -1;

    for (int i = 0; i < n; i++) {
        if (!processes[i].isCompleted && processes[i].arrivalTime <= currentTime) {
            if (processes[i].burstTime < minBurstTime ||
                (processes[i].burstTime == minBurstTime && processes[i].arrivalTime < processes[index].arrivalTime)) {
                minBurstTime = processes[i].burstTime;
                index = i;
            }
        }
    }
    return index;
}

void nonPreemptiveSJF(Process processes[], int n) {
    int completed = 0, currentTime = 0;
    float totalWaitingTime = 0, totalTurnaroundTime = 0;

    // Initialize completion flag for each process
    for (int i = 0; i < n; i++) {
        processes[i].isCompleted = 0;
    }

    while (completed < n) {
        int index = findShortestJob(processes, n, currentTime);

        if (index != -1) {
            // Process the selected process
            currentTime += processes[index].burstTime;
            processes[index].isCompleted = 1;
            completed++;

            // Calculate waiting and turnaround times
            processes[index].turnaroundTime = currentTime - processes[index].arrivalTime;
            processes[index].waitingTime = processes[index].turnaroundTime - processes[index].burstTime;

            totalWaitingTime += processes[index].waitingTime;
            totalTurnaroundTime += processes[index].turnaroundTime;
        } else {
            // If no process is ready, increment time
            currentTime++;
        }
    }

    // Print results
    printf("\nProcess\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n",
               processes[i].id, processes[i].arrivalTime, processes[i].burstTime,
               processes[i].waitingTime, processes[i].turnaroundTime);
    }

    printf("\nAverage Waiting Time: %.2f\n", totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnaroundTime / n);
}

int main() {
    int n;
    Process processes[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nEnter details for Process P%d\n", i + 1);
        processes[i].id = i + 1;
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrivalTime);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burstTime);
    }

    nonPreemptiveSJF(processes, n);

    return 0;
}

