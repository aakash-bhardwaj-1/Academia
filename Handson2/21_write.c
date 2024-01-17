#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd1, fd2;

    // Open the FIFO for writing
    fd1 = open("20_fifo", O_WRONLY);
    if (fd1 == -1) {
        perror("open");
        return 1;
    }

    // Open the same FIFO for reading
    fd2 = open("20_fifo", O_RDONLY);
    if (fd2 == -1) {
        perror("open");
        close(fd1); // Close the first file descriptor on error
        return 1;
    }

   char buffer[100];
    //  memset(buffer, 0, 100);

    printf("Enter text: ");
    scanf(" %[^\n]", buffer);

    // Write data to the FIFO using fd1
    ssize_t bytesWritten = write(fd1, buffer, 100);

    if (bytesWritten == -1) {
        perror("write");
        close(fd1);
        close(fd2);
        return 1;
    }

    // Read data from the FIFO using fd2
    ssize_t bytesRead = read(fd2, buffer, 100);
    if (bytesRead == -1) {
        perror("read");
        close(fd1);
        close(fd2);
        return 1;
    }

    printf("Data read from FIFO: %s\n", buffer);

    close(fd1);
    close(fd2);

    return 0;
}

