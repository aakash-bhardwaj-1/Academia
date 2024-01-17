#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main() {
    int queueIdentifier;
    struct msqid_ds metadata;
    int msgctlStatus;

    key_t key = ftok(".", 1);

    if (key == -1) {
        perror("Error while computing key!");
        exit(0);
    }

    queueIdentifier = msgget(key, IPC_CREAT | 0700);
    if (queueIdentifier == -1) {
        perror("Error while creating Message Queue!");
        exit(0);
    }

    printf("Key: %d\n", key);
    printf("Message Queue Identifier: %d\n\n", queueIdentifier);

    msgctlStatus = msgctl(queueIdentifier, IPC_STAT, &metadata);

    if (msgctlStatus == -1) {
        perror("Error while getting Message Queue info!");
        exit(0);
    }

    printf("current access Permission: %o\n", metadata.msg_perm.mode);
  
  printf("press enter to change permissions");
  getchar();
  getchar();
  metadata.msg_perm.mode=0644;
  
  printf("updated access Permission: %o\n", metadata.msg_perm.mode);
    

    return 0;
}

