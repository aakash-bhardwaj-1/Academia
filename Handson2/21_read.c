#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd1, fd2;

    // Open the FIFO for reading
    fd1 = open("20_fifo", O_RDONLY);
    if (fd1 == -1) {
        perror("open");
        return 1;
    }

    // Open the same FIFO for writing
    fd2 = open("20_fifo", O_WRONLY);
    if (fd2 == -1) {
        perror("open");
        close(fd1); // Close the first file descriptor on error
        return 1;
    }

    char buffer[100];
    memset(buffer, 0, sizeof(buffer));

    ssize_t bytesRead = read(fd1, buffer, 100);

    if (bytesRead == -1) {
        perror("read");
        close(fd1);
        close(fd2);
        return 1;
    }

    printf("Data read from FIFO: %s\n", buffer);

    printf("Enter text: ");
    scanf(" %[^\n]", buffer);

    ssize_t bytesWritten = write(fd2, buffer, 100);

    if (bytesWritten == -1) {
        perror("write");
        close(fd1);
        close(fd2);
        return 1;
    }

    close(fd1);
    close(fd2);

    return 0;
}

