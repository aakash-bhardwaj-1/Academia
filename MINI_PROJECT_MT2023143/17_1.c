/*
============================================================================
Name : 17_1.c
Author : Aakash Bhardwaj
Description : Write a program to open a file, store a ticket no and exit
Date: 21th Aug, 2023.
============================================================================
*/

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
int main(){
	int fd1 = open("generate_sid_file.txt", O_CREAT|O_RDWR,0666);
	int fd2 = open("generate_fid_file.txt", O_CREAT|O_RDWR,0666);
	int fd3 = open("generate_cid_file.txt", O_CREAT|O_RDWR,0666);
	int buf  = 0;
	write(fd1, &buf, sizeof(buf));

	write(fd2, &buf, sizeof(buf));
	write(fd3, &buf, sizeof(buf));

	close(fd1);
	close(fd2);
}

