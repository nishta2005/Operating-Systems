#include <stdio.h>
#include <string.h>

// Define a structure to hold process details
struct Process {
    int pid;               // Process ID
    char name[50];         // Process Name
    int arrival_time;      // Process Arrival Time
    int completion_time;   // Process Completion Time
    int execution_time;    // Process Execution Time
};

int main() {
    int n, i;

    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Declare an array of structures to hold the details of the processes
    struct Process processes[n];

    // Input process details for each process
    for (i = 0; i < n; i++) {
        printf("\nEnter details for Process %d\n", i + 1);
        processes[i].pid = i + 1;  // Assign a unique process Id

        printf("Enter process name: ");
        scanf("%s", processes[i].name);

        printf("Enter arrival time: ");
        scanf("%d", &processes[i].arrival_time);

        printf("Enter completion time: ");
        scanf("%d", &processes[i].completion_time);

        printf("Enter execution time: ");
        scanf("%d", &processes[i].execution_time);
    }

    // Display the entered process details
    printf("\nProcess Details:\n");
    printf("---------------------------------------------------------------\n");
    printf("| PID | Process Name | Arrival Time | Completion Time | Execution Time |\n");
    printf("---------------------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("| %3d | %-12s | %12d | %15d | %15d |\n",
            processes[i].pid, processes[i].name, processes[i].arrival_time,
            processes[i].completion_time, processes[i].execution_time);
    }

    return 0;
}
