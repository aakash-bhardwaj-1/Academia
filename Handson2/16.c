#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int pair_fd[2];
    int pair_fd2[2];
    
    if (pipe(pair_fd) == -1) {
        printf("pipe not created");
        return 0;
    }

    if (pipe(pair_fd2) == -1) {
        printf("pipe not created");
        return 0;
    }

    pid_t id = fork();

    if (id == 0) {
        // Inside the child
        // Child is reading the parent's data
        close(pair_fd[1]);  // Close the write end of pair_fd
        close(pair_fd2[0]); // Close the read end of pair_fd2
        
        int x;
        read(pair_fd[0], &x, sizeof(int));
        printf("Value of X read in child is %d\n", x);

        printf("Enter the value of X to be sent to the parent\n");
        scanf("%d", &x);
        write(pair_fd2[1], &x, sizeof(int));

        close(pair_fd[0]);
        close(pair_fd2[1]);
    } else {
        // Inside the parent
        // Writing data for the child
        close(pair_fd[0]);  // Close the read end of pair_fd
        close(pair_fd2[1]); // Close the write end of pair_fd2
        
        int x;
        printf("Enter the value of X to be sent to the child\n");
        scanf("%d", &x);
        write(pair_fd[1], &x, sizeof(int));

        read(pair_fd2[0], &x, sizeof(int));
        printf("Value of X read in parent is %d\n", x);

        close(pair_fd[1]);
        close(pair_fd2[0]);
    }

    return 0;
}

