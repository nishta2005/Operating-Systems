#include <stdio.h>

struct Process {
    int pid;        // Process ID
    int bt;         // Burst time
    int at;         // Arrival time
    int wt;         // Waiting time
    int tat;        // Turnaround time
    int priority;   // Priority
    int rem_bt;     // Remaining burst time for Round Robin
};

// Round Robin Scheduling
void findWaitingTimeRR(struct Process proc[], int n, int quantum) {
    for (int i = 0; i < n; i++) {
        proc[i].rem_bt = proc[i].bt;
    }

    int t = 0; // Current time
    while (1) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (proc[i].rem_bt > 0) {
                done = 0;
                if (proc[i].rem_bt > quantum) {
                    t += quantum;
                    proc[i].rem_bt -= quantum;
                } else {
                    t += proc[i].rem_bt;
                    proc[i].wt = t - proc[i].bt - proc[i].at;
                    proc[i].rem_bt = 0;
                }
            }
        }
        if (done == 1) {
            break;
        }
    }
}

void findTurnaroundTimeRR(struct Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].tat = proc[i].bt + proc[i].wt;
    }
}

void findAverageTimeRR(struct Process proc[], int n) {
    int total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += proc[i].wt;
        total_tat += proc[i].tat;
    }

    printf("Round Robin Scheduling:\n");
    printf("Average waiting time: %.2f\n", (float)total_wt / n);
    printf("Average turnaround time: %.2f\n\n", (float)total_tat / n);
}

// Priority Scheduling
void findWaitingTimePriority(struct Process proc[], int n) {
    proc[0].wt = 0; // The first process has no waiting time

    for (int i = 1; i < n; i++) {
        proc[i].wt = proc[i - 1].bt + proc[i - 1].wt;
    }
}

void findTurnaroundTimePriority(struct Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].tat = proc[i].bt + proc[i].wt;
    }
}

void findAverageTimePriority(struct Process proc[], int n) {
    int total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += proc[i].wt;
        total_tat += proc[i].tat;
    }

    printf("Priority Scheduling:\n");
    printf("Average waiting time: %.2f\n", (float)total_wt / n);
    printf("Average turnaround time: %.2f\n\n", (float)total_tat / n);
}

void priorityScheduling(struct Process proc[], int n) {
    // Sorting processes by priority
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].priority > proc[j].priority) {
                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }

    findWaitingTimePriority(proc, n);
    findTurnaroundTimePriority(proc, n);
    findAverageTimePriority(proc, n);
}

// Main function
int main() {
    int n, choice;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &proc[i].bt);
        printf("Enter arrival time for Process %d: ", i + 1);
        scanf("%d", &proc[i].at);
    }

    printf("\nChoose Scheduling Algorithm:\n");
    printf("1. Round Robin Scheduling\n");
    printf("2. Priority Scheduling\n");
    printf("Enter choice (1 or 2): ");
    scanf("%d", &choice);

    if (choice == 1) {
        int quantum;
        printf("Enter time quantum for Round Robin: ");
        scanf("%d", &quantum);

        findWaitingTimeRR(proc, n, quantum);
        findTurnaroundTimeRR(proc, n);
        findAverageTimeRR(proc, n);
    } else if (choice == 2) {
        for (int i = 0; i < n; i++) {
            printf("Enter priority for Process %d (lower number means higher priority): ", i + 1);
            scanf("%d", &proc[i].priority);
        }

        priorityScheduling(proc, n);
    } else {
        printf("Invalid choice!\n");
    }

    return 0;
}


