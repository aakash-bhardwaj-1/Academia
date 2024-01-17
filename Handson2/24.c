#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    int key = ftok("/home/aakash/Desktop/Hands on 2/24", 'b');
    int msgid = msgget(key, IPC_CREAT | IPC_EXCL | 0744);

    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    printf("Key=0x%0x\nmsgid=%d\n", key, msgid);

    return 0;
}

