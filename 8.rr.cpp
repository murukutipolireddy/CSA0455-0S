#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 100

typedef struct {
    int id;            // Process ID
    int arrivalTime;   // Arrival Time
    int burstTime;     // Burst Time
    int remainingTime; // Remaining Burst Time
    int waitingTime;   // Waiting Time
    int turnaroundTime; // Turnaround Time
} Process;

void roundRobinScheduling(Process processes[], int n, int timeQuantum) {
    int currentTime = 0;
    int completed = 0;
    float totalWaitingTime = 0, totalTurnaroundTime = 0;
    bool done = false;

    // Initialize remaining time for all processes
    for (int i = 0; i < n; i++) {
        processes[i].remainingTime = processes[i].burstTime;
    }

    printf("\nGantt Chart:\n");

    while (completed < n) {
        done = true;
        for (int i = 0; i < n; i++) {
            if (processes[i].remainingTime > 0) {
                done = false;

                // Check if process executes within time quantum
                if (processes[i].remainingTime <= timeQuantum) {
                    currentTime += processes[i].remainingTime;
                    printf(" P%d ", processes[i].id); // Add to Gantt Chart
                    processes[i].remainingTime = 0;
                    completed++;

                    // Calculate waiting and turnaround times
                    processes[i].turnaroundTime = currentTime - processes[i].arrivalTime;
                    processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;

                    totalWaitingTime += processes[i].waitingTime;
                    totalTurnaroundTime += processes[i].turnaroundTime;
                } else {
                    currentTime += timeQuantum;
                    processes[i].remainingTime -= timeQuantum;
                    printf(" P%d ", processes[i].id); // Add to Gantt Chart
                }
            }
        }

        if (done) break; // All processes are completed
    }

    printf("\n\nProcess\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n",
               processes[i].id, processes[i].arrivalTime, processes[i].burstTime,
               processes[i].waitingTime, processes[i].turnaroundTime);
    }

    printf("\nAverage Waiting Time: %.2f\n", totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnaroundTime / n);
}

int main() {
    int n, timeQuantum;
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

    printf("\nEnter the Time Quantum: ");
    scanf("%d", &timeQuantum);

    roundRobinScheduling(processes, n, timeQuantum);

    return 0;
}

