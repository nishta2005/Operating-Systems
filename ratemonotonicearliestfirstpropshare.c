#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_TASKS 10

typedef struct {
    int id;
    int period;
    int execution_time;
    int deadline;
    int remaining_time;
    int next_release_time;
    int next_deadline;
} Task;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int lcm(int a, int b) {
    return a * b / gcd(a, b);
}

int get_hyperperiod(Task tasks[], int n) {
    int hp = tasks[0].period;
    for (int i = 1; i < n; i++) {
        hp = lcm(hp, tasks[i].period);
    }
    return hp;
}

void reset_tasks(Task tasks[], int n) {
    for (int i = 0; i < n; i++) {
        tasks[i].remaining_time = 0;
        tasks[i].next_release_time = 0;
        tasks[i].next_deadline = tasks[i].deadline;
    }
}

void rate_monotonic(Task tasks[], int n) {
    printf("\n--- Rate Monotonic Scheduling ---\n");
    reset_tasks(tasks, n);
    int hyperperiod = get_hyperperiod(tasks, n);

    for (int time = 0; time < hyperperiod; time++) {
        for (int i = 0; i < n; i++) {
            if (time == tasks[i].next_release_time) {
                tasks[i].remaining_time = tasks[i].execution_time;
                tasks[i].next_release_time += tasks[i].period;
            }
        }

        int selected = -1;
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining_time > 0) {
                if (selected == -1 || tasks[i].period < tasks[selected].period) {
                    selected = i;
                }
            }
        }

        if (selected != -1) {
            printf("Time %2d: Task %d\n", time, tasks[selected].id);
            tasks[selected].remaining_time--;
        } else {
            printf("Time %2d: Idle\n", time);
        }
    }
}

void earliest_deadline_first(Task tasks[], int n) {
    printf("\n--- Earliest Deadline First Scheduling ---\n");
    reset_tasks(tasks, n);
    int hyperperiod = get_hyperperiod(tasks, n);

    for (int time = 0; time < hyperperiod; time++) {
        for (int i = 0; i < n; i++) {
            if (time == tasks[i].next_release_time) {
                tasks[i].remaining_time = tasks[i].execution_time;
                tasks[i].next_deadline = time + tasks[i].deadline;
                tasks[i].next_release_time += tasks[i].period;
            }
        }

        int selected = -1;
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining_time > 0) {
                if (selected == -1 || tasks[i].next_deadline < tasks[selected].next_deadline) {
                    selected = i;
                }
            }
        }

        if (selected != -1) {
            printf("Time %2d: Task %d\n", time, tasks[selected].id);
            tasks[selected].remaining_time--;
        } else {
            printf("Time %2d: Idle\n", time);
        }
    }
}

void proportional_share(Task tasks[], int n) {
    printf("\n--- Proportional Share Scheduling ---\n");
    int total = 0;
    for (int i = 0; i < n; i++)
        total += tasks[i].execution_time;

    for (int time = 0, i = 0; time < 20; time++) {
        int task_time = tasks[i].execution_time;
        for (int j = 0; j < task_time && time < 20; j++, time++) {
            printf("Time %2d: Task %d\n", time, tasks[i].id);
        }
        i = (i + 1) % n;
        time--;  // adjust for loop increment
    }
}

int main() {
    Task tasks[MAX_TASKS];
    int n;

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    printf("Enter task details:\n");
    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;
        printf("Task %d - Period: ", i + 1);
        scanf("%d", &tasks[i].period);
        printf("         Execution Time: ");
        scanf("%d", &tasks[i].execution_time);
        printf("         Deadline: ");
        scanf("%d", &tasks[i].deadline);
    }

    rate_monotonic(tasks, n);
    earliest_deadline_first(tasks, n);
    proportional_share(tasks, n);

    return 0;
}
