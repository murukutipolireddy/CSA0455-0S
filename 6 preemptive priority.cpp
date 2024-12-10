#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 100

typedef struct {
    int pid;           // Process ID
    int arrivalTime;   // Arrival time
    int burstTime;     // Burst time
    int priority;      // Priority (lower value = higher priority)
    int remainingTime; // Remaining burst time
    int waitingTime;   // Waiting time
    int turnaroundTime; // Turnaround time
    bool completed;    // Completion status
} Process;

// Function to find the next process to execute
int findNextProcess(Process processes[], int n, int currentTime) {
    int highestPriority = __INT_MAX__;
    int nextProcessIndex = -1;

    for (int i = 0; i < n; i++) {
        if (processes[i].remainingTime > 0 && processes[i].arrivalTime <= currentTime) {
            if (processes[i].priority < highestPriority || 
                (processes[i].priority == highestPriority && processes[i].arrivalTime < processes[nextProcessIndex].arrivalTime)) {
                highestPriority = processes[i].priority;
                nextProcessIndex = i;
            }
        }
    }

    return nextProcessIndex;
}

int main() {
    int n;
    Process processes[MAX_PROCESSES];
    int currentTime = 0, completedProcesses = 0;
    float totalWaitingTime = 0, totalTurnaroundTime = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time for process P%d: ", processes[i].pid);
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter burst time for process P%d: ", processes[i].pid);
        scanf("%d", &processes[i].burstTime);
        printf("Enter priority for process P%d (lower value = higher priority): ", processes[i].pid);
        scanf("%d", &processes[i].priority);
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].completed = false;
    }

    printf("\nGantt Chart:\n");
    printf("|");

    // Process scheduling loop
    while (completedProcesses < n) {
        int nextProcessIndex = findNextProcess(processes, n, currentTime);

        if (nextProcessIndex == -1) {
            // No process is ready, increment time
            printf(" IDLE ");
            currentTime++;
        } else {
            Process *p = &processes[nextProcessIndex];
            printf(" P%d ", p->pid);

            // Execute the process for 1 time unit
            p->remainingTime--;
            currentTime++;

            // If the process is completed
            if (p->remainingTime == 0) {
                p->completed = true;
                completedProcesses++;
                p->turnaroundTime = currentTime - p->arrivalTime;
                p->waitingTime = p->turnaroundTime - p->burstTime;

                // Update totals
                totalWaitingTime += p->waitingTime;
                totalTurnaroundTime += p->turnaroundTime;
            }
        }
        printf("|");
    }

    // Display results
    printf("\n\nProcess\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].pid,
               processes[i].arrivalTime,
               processes[i].burstTime,
               processes[i].priority,
               processes[i].waitingTime,
               processes[i].turnaroundTime);
    }

    printf("\nAverage Waiting Time: %.2f\n", totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnaroundTime / n);

    return 0;
}

