/*
============================================================================
Name : 13.c
Author : Aakash Bhardwaj
Description : Write a program to wait for a STDIN for 10 seconds using select. Write a proper print statement to
	      verify whether the data is available within 10 seconds or not (check in $man 2 select).
Date: 28th Aug, 2023.
============================================================================
*/
#include<stdio.h>
#include<stdlib.h>
#include <sys/select.h>
#include<unistd.h>
#include<fcntl.h>
int main(){
	fd_set rfds;// fd_set type is actually an array of long type. For convenience, suppose fd_set is 1 byte in length. Each bit in fd_set can correspond to a file descriptor (fd), then a 1-byte long fd_set can correspond to a maximum of 8 fds. Execute fd_set set; FD_ZERO(&set); The set is expressed in bits as 0000,0000.
	struct timeval tv;
	int ret;
	
	FD_ZERO(&rfds);
	FD_SET(0,&rfds);
	
	tv.tv_sec=10;
	tv.tv_usec=0;
	ret=select(1,&rfds,NULL,NULL,&tv);
	
	if(ret)
		printf("Data is available within 10 sec\n");
	else
		printf("Data is not available within 10 sec\n");
}
