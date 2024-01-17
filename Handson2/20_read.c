#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd = open("20_fifo", O_RDONLY);
    
    if (fd == -1) {
        perror("open");
        return 1;
    }

    char buffer[100];
    memset(buffer, 0, sizeof(buffer));

    ssize_t bytesRead = read(fd, buffer, sizeof(buffer));

    if (bytesRead == -1) {
        perror("read");
        close(fd);
        return 1;
    }

    close(fd);
    
    printf("Data read from FIFO: %s\n", buffer);

    return 0;
}

