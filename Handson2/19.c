#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    char *fifo1 = "./mymkfifo";
    char *fifo2 = "./mymknod-fifo";

    int result1, result2;

    result1 = mkfifo(fifo1, 0777);

    if (result1 == -1) {
        perror("Error creating FIFO file using mkfifo");
    } else {
        printf("FIFO file created using mkfifo. Check with `ls -l` or `ll` command!\n");
    }

    result2 = mknod(fifo2, __S_IFIFO | 0777, 0);

    if (result2 == -1) {
        perror("Error creating FIFO file using mknod");
    } else {
        printf("FIFO file created using mknod. Check with `ls -l` or `ll` command!\n");
    }

    return 0;
}

