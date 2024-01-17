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

    key_t key = ftok("/home/aakash/Desktop/Hands on 2/24", 'b');

    if (key == -1) {
        perror("Error while computing key!");
        exit(0);
    }

    queueIdentifier = msgget(key, 0);
    if (queueIdentifier == -1) {
        perror("Error while creating Message Queue!");
        exit(0);
    }

    printf("Key: %d\n", key);
    printf("Message Queue Identifier: %d\n\n", queueIdentifier);

    msgctlStatus = msgctl(queueIdentifier, IPC_RMID, NULL);

    if (msgctlStatus == -1) {
        perror("Error while getting Message Queue info!");
        exit(0);
    }

    
    

    return 0;
}

