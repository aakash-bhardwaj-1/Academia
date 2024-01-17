#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// Define a structure for your message
struct MyMessage {
    long mtype;  // Used to identify message type (should be > 0)
    int data;    // Integer data
};

int main() {
    // Generate a unique key using ftok
    int key = ftok("/home/aakash/Desktop/Hands on 2/24", 'a');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Create or get a message queue
    int msgid = msgget(key, IPC_CREAT | 0744);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    // Print the generated key and message queue ID
    printf("Key=0x%0x\nmsgid=%d\n", key, msgid);

    // Prepare your message
   struct MyMessage content;
    content.mtype = 1;
    

    // Send the message
    if (msgrcv(msgid, &content , sizeof(content), content.mtype, IPC_NOWAIT) == -1) {
        perror("msgsnd");
        exit(1);
    }

    printf("Message Received! %d\n", content.data);

    return 0;
}

