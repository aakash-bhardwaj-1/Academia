#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE 100

int main() {
    int shmid;
    key_t key;
    char *shmaddress;

    key = ftok(".", 'a');
    printf("Key generated is : %d\n",key);
    shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);

    if (shmid == -1) {
        perror("Error in shmget function");
        return 0;
    }

    shmaddress = shmat(shmid, NULL, 0);

    if ((shmaddress == (char *)-1)) {
        perror("Error in shmat function ");
        return 0;
    }
    char buff[SHM_SIZE];
    printf("Enter the text you want to write to shared memory\n");
    scanf("%[^\n]",buff);
    strcpy(shmaddress, buff);

    if (shmdt(shmaddress) == -1) {
        perror("Error in shmdt function");
        return 0;
    }

    shmaddress = shmat(shmid, NULL, SHM_RDONLY);

    if (shmaddress == (char *)-1) {
        perror("Error in shmat function");
        return 0;
    }
    
    //strcpy(shmaddr, "This should not overwrite!"); if we try to ovewrite on the shared memory which in RDONLY then it gives segmentation fault
    printf("Contents of shared memory: %s\n", shmaddress);
    if (shmdt(shmaddress) == -1) {
        perror("Error in shmdt function");
        return 0;
    }

    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("Error in shmctl function");
        return 0;
    }

    return 0;
}

