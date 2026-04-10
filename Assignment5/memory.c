#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Structure for memory block
struct block {
    int size;
    int free;
    int pid;
};

struct block memory[MAX];
int n;

// Initialize memory
void initialize_memory() {
    printf("Enter number of memory blocks: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        printf("Enter size of block %d: ", i+1);
        scanf("%d", &memory[i].size);
        memory[i].free = 1;
        memory[i].pid = -1;
    }
}

// Display memory
void display() {
    printf("\nMemory Status:\n");
    for(int i = 0; i < n; i++) {
        if(memory[i].free)
            printf("Block %d: Free (%d KB)\n", i+1, memory[i].size);
        else
            printf("Block %d: Process %d (%d KB)\n", i+1, memory[i].pid, memory[i].size);
    }
}

// First Fit
void first_fit(int pid, int size) {
    for(int i = 0; i < n; i++) {
        if(memory[i].free && memory[i].size >= size) {
            memory[i].free = 0;
            memory[i].pid = pid;
            printf("Allocated using First Fit\n");
            return;
        }
    }
    printf("Allocation Failed\n");
}

// Best Fit
void best_fit(int pid, int size) {
    int best = -1;
    for(int i = 0; i < n; i++) {
        if(memory[i].free && memory[i].size >= size) {
            if(best == -1 || memory[i].size < memory[best].size)
                best = i;
        }
    }

    if(best != -1) {
        memory[best].free = 0;
        memory[best].pid = pid;
        printf("Allocated using Best Fit\n");
    } else {
        printf("Allocation Failed\n");
    }
}

// Worst Fit
void worst_fit(int pid, int size) {
    int worst = -1;
    for(int i = 0; i < n; i++) {
        if(memory[i].free && memory[i].size >= size) {
            if(worst == -1 || memory[i].size > memory[worst].size)
                worst = i;
        }
    }

    if(worst != -1) {
        memory[worst].free = 0;
        memory[worst].pid = pid;
        printf("Allocated using Worst Fit\n");
    } else {
        printf("Allocation Failed\n");
    }
}

// Free memory
void free_memory(int pid) {
    for(int i = 0; i < n; i++) {
        if(memory[i].pid == pid) {
            memory[i].free = 1;
            memory[i].pid = -1;
            printf("Process %d Freed\n", pid);
            return;
        }
    }
    printf("Process not found\n");
}

// Main
int main() {
    int choice, size, pid = 1;

    initialize_memory();

    while(1) {
        printf("\n1. First Fit\n2. Best Fit\n3. Worst Fit\n4. Free Memory\n5. Display\n6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter process size: ");
                scanf("%d", &size);
                first_fit(pid++, size);
                break;

            case 2:
                printf("Enter process size: ");
                scanf("%d", &size);
                best_fit(pid++, size);
                break;

            case 3:
                printf("Enter process size: ");
                scanf("%d", &size);
                worst_fit(pid++, size);
                break;

            case 4:
                printf("Enter process id to free: ");
                scanf("%d", &pid);
                free_memory(pid);
                break;

            case 5:
                display();
                break;

            case 6:
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }
}
