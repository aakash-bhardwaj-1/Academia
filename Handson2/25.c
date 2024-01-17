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

    printf("Access Permission: %o\n", metadata.msg_perm.mode);
    printf("UID: %d\n", metadata.msg_perm.uid);
    printf("GID: %d\n", metadata.msg_perm.gid);
    printf("Time of last message sent: %ld\n", metadata.msg_stime);
    printf("Time of last message received: %ld\n", metadata.msg_rtime);
    printf("Size of queue: %ld\n", metadata.msg_cbytes);
    printf("Number of messages in the queue: %ld\n", metadata.msg_qnum);
    printf("Maximum number of bytes allowed in the queue: %ld\n", metadata.msg_qbytes);
    printf("PID of last sent message: %d\n", metadata.msg_lspid);
    printf("PID of last received message: %d\n", metadata.msg_lrpid);

    return 0;
}

