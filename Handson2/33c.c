#include <sys/types.h>  
#include <sys/socket.h> 
#include <netinet/ip.h> 
#include <stdio.h>   
#include <unistd.h>  
#include <stdlib.h>

void main()
{
    int sd; 
    int connectStatus;        
    struct sockaddr_in address; // for ipV4

    ssize_t readBytes, writeBytes; 
    char dataFromServer[100];

   
    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd == -1)
    {
        perror("Error");
        exit(0);
    }
    printf("Client side socket successfully created!\n");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
   
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    address.sin_family = AF_INET; // AF_INET for IPv4. 
    address.sin_port = htons(8000);

    connectStatus = connect(sd, (struct sockaddr *)&address, sizeof(address));
    if (connectStatus == -1)
    {
        perror("Error while connecting to server!");
        exit(0);
    }
    printf("Client to server connection successful\n");

    
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    readBytes = read(sd, dataFromServer, 100);
    
    if (readBytes == -1)
        perror("Error while reading from network via socket!");
    else
        printf("Data from server: %s\n", dataFromServer);
        
        
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    writeBytes = write(sd, "client side", 11);
    if (writeBytes == -1)
        perror("Error while writing to network via socket!");
    else
        printf("Data sent to server!");
    

    

    close(sd);
}
