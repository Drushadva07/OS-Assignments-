#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd;

    fd = open("file.txt", O_CREAT | O_RDWR, 0644);
    write(fd, "Hello\n", 6);
    close(fd);

    printf("Done\n");

    return 0;
}
