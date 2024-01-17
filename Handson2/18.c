#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main() {
    int pipe_ls_to_grep[2], pipe_grep_to_wc[2];
    int pipe_ls_status, pipe_grep_status;

    pid_t child_ls, child_grep, child_wc;

    pipe_ls_status = pipe(pipe_ls_to_grep);
    pipe_grep_status = pipe(pipe_grep_to_wc);

    if (pipe_ls_status == -1 || pipe_grep_status == -1) {
        perror("Error while creating the pipe!");
    } else {
        child_ls = fork();

        if (child_ls == -1) {
            perror("Error while creating the ls child!");
        } else if (child_ls == 0) {
            // Child process for 'ls -l'
            close(pipe_grep_to_wc[1]);
            close(pipe_ls_to_grep[0]);

            close(STDIN_FILENO);
            dup2(pipe_grep_to_wc[0], STDIN_FILENO);

            execl("/usr/bin/wc", "wc", NULL);
        } else {
            child_grep = fork();

            if (child_grep == -1) {
                perror("Error while creating the grep child!");
            } else if (child_grep == 0) {
                // Child process for 'grep ^d'
                close(pipe_ls_to_grep[1]);
                close(pipe_grep_to_wc[0]);

                close(STDIN_FILENO);
                dup2(pipe_ls_to_grep[0], STDIN_FILENO);

                close(STDOUT_FILENO);
                dup2(pipe_grep_to_wc[1], STDOUT_FILENO);

                execl("/usr/bin/grep", "grep", "^d", NULL);
            } else {
                // Parent process for 'ls -l'
                close(pipe_ls_to_grep[0]);
                close(pipe_grep_to_wc[1]);
                close(pipe_grep_to_wc[0]);

                close(STDOUT_FILENO);
                dup2(pipe_ls_to_grep[1], STDOUT_FILENO);

                execl("/usr/bin/ls", "ls", "-l", NULL);

                // Add code to display the output on the screen
                dup2(STDOUT_FILENO, STDOUT_FILENO);
                execl("/usr/bin/cat", "cat", NULL);
            }
        }
    }

    return 0;
}

