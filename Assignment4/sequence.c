#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Usage: %s <positive number>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);

    if (n <= 0) {
        printf("Enter a positive integer\n");
        return 1;
    }

    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        printf("Sequence: ");
        while (n != 1) {
            printf("%d ", n);
            if (n % 2 == 0)
                n = n / 2;
            else
                n = 3 * n + 1;
        }
        printf("1\n");
    } 
    else {
        wait(NULL);
        printf("Parent finished\n");
    }

    return 0;
}
