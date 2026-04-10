#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

struct Process {
    int pid;
    int arrival;
    int burst;
    int remaining;
    int completion;
    int turnaround;
    int waiting;
    int response;
    int started;
};

// Function to generate random processes
void generateProcesses(struct Process p[], int n) {
    srand(time(0));
    FILE *fp = fopen("process_data.tex", "w");

    fprintf(fp, "PID\tArrival\tBurst\n");

    for(int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        p[i].arrival = rand() % 10;
        p[i].burst = rand() % 10 + 1;
        p[i].remaining = p[i].burst;
        p[i].started = 0;

        fprintf(fp, "%d\t%d\t%d\n", p[i].pid, p[i].arrival, p[i].burst);
    }

    fclose(fp);
}

// FCFS Scheduling
void fcfs(struct Process p[], int n, FILE *fp) {
    int time = 0;
    float avg_wt = 0, avg_tat = 0, avg_rt = 0;

    fprintf(fp, "\n--- FCFS ---\n");

    for(int i = 0; i < n; i++) {
        if(time < p[i].arrival)
            time = p[i].arrival;

        p[i].response = time - p[i].arrival;
        time += p[i].burst;
        p[i].completion = time;
        p[i].turnaround = p[i].completion - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;

        avg_wt += p[i].waiting;
        avg_tat += p[i].turnaround;
        avg_rt += p[i].response;

        fprintf(fp, "P%d WT=%d TAT=%d RT=%d\n",
                p[i].pid, p[i].waiting, p[i].turnaround, p[i].response);
    }

    fprintf(fp, "AVG WT=%.2f\n", avg_wt/n);
    fprintf(fp, "AVG TAT=%.2f\n", avg_tat/n);
    fprintf(fp, "AVG RT=%.2f\n", avg_rt/n);
}

// SJF Scheduling (Non-preemptive)
void sjf(struct Process p[], int n, FILE *fp) {
    int completed = 0, time = 0;
    int isCompleted[MAX] = {0};

    float avg_wt = 0, avg_tat = 0, avg_rt = 0;

    fprintf(fp, "\n--- SJF ---\n");

    while(completed != n) {
        int idx = -1;
        int minBurst = 9999;

        for(int i = 0; i < n; i++) {
            if(p[i].arrival <= time && !isCompleted[i]) {
                if(p[i].burst < minBurst) {
                    minBurst = p[i].burst;
                    idx = i;
                }
            }
        }

        if(idx != -1) {
            if(time < p[idx].arrival)
                time = p[idx].arrival;

            p[idx].response = time - p[idx].arrival;
            time += p[idx].burst;

            p[idx].completion = time;
            p[idx].turnaround = p[idx].completion - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;

            avg_wt += p[idx].waiting;
            avg_tat += p[idx].turnaround;
            avg_rt += p[idx].response;

            isCompleted[idx] = 1;
            completed++;

            fprintf(fp, "P%d WT=%d TAT=%d RT=%d\n",
                    p[idx].pid, p[idx].waiting, p[idx].turnaround, p[idx].response);
        } else {
            time++;
        }
    }

    fprintf(fp, "AVG WT=%.2f\n", avg_wt/n);
    fprintf(fp, "AVG TAT=%.2f\n", avg_tat/n);
    fprintf(fp, "AVG RT=%.2f\n", avg_rt/n);
}

// Round Robin
void roundRobin(struct Process p[], int n, int quantum, FILE *fp) {
    int time = 0, completed = 0;
    float avg_wt = 0, avg_tat = 0, avg_rt = 0;

    fprintf(fp, "\n--- Round Robin (Q=%d) ---\n", quantum);

    while(completed < n) {
        int done = 1;

        for(int i = 0; i < n; i++) {
            if(p[i].remaining > 0) {
                done = 0;

                if(!p[i].started) {
                    p[i].response = time - p[i].arrival;
                    p[i].started = 1;
                }

                if(p[i].remaining > quantum) {
                    time += quantum;
                    p[i].remaining -= quantum;
                } else {
                    time += p[i].remaining;
                    p[i].remaining = 0;
                    completed++;

                    p[i].completion = time;
                    p[i].turnaround = p[i].completion - p[i].arrival;
                    p[i].waiting = p[i].turnaround - p[i].burst;

                    avg_wt += p[i].waiting;
                    avg_tat += p[i].turnaround;
                    avg_rt += p[i].response;

                    fprintf(fp, "P%d WT=%d TAT=%d RT=%d\n",
                            p[i].pid, p[i].waiting, p[i].turnaround, p[i].response);
                }
            }
        }

        if(done) break;
    }

    fprintf(fp, "AVG WT=%.2f\n", avg_wt/n);
    fprintf(fp, "AVG TAT=%.2f\n", avg_tat/n);
    fprintf(fp, "AVG RT=%.2f\n", avg_rt/n);
}

// MAIN FUNCTION
int main() {
    int n, choice, quantum;

    struct Process p[MAX], copy[MAX];

    printf("CPU Scheduling Simulator\n");
    printf("1. FCFS\n2. SJF\n3. Round Robin\n4. All\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    printf("Enter number of processes: ");
    scanf("%d", &n);

    generateProcesses(p, n);

    FILE *fp = fopen("output.tex", "w");

    // Copy original data
    for(int i = 0; i < n; i++)
        copy[i] = p[i];

    if(choice == 1 || choice == 4)
        fcfs(copy, n, fp);

    for(int i = 0; i < n; i++)
        copy[i] = p[i];

    if(choice == 2 || choice == 4)
        sjf(copy, n, fp);

    for(int i = 0; i < n; i++)
        copy[i] = p[i];

    if(choice == 3 || choice == 4) {
        printf("Enter Time Quantum: ");
        scanf("%d", &quantum);
        roundRobin(copy, n, quantum, fp);
    }

    fclose(fp);

    printf("\nDONE. Check output.tex file\n");

    return 0;
}
