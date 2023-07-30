//changed the port to 1235 from 1234 to see if it works. but it is not connecting to the server. 
#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>

#define myport 1235
//#define myport 1234	//this works. it displayes the msg as  the second client. 
int main()
{
	int sockfd, size, acptfd;
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in dest_addr;
	
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(myport);
	dest_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //this has to do something with the local host
	memset(dest_addr.sin_zero, '\0', sizeof(dest_addr.sin_zero));
	
	//client doesnt have to bind. it has to connect to the server now
	
	connect(sockfd, (struct sockaddr *) &dest_addr, sizeof(struct sockaddr));
	char buffer[20] = "hello np 2! i am the second client";
	send(sockfd, buffer, 20,0);
	recv(sockfd, buffer, 20, 0);
	printf("Echoed data  = %s", buffer);
	
	strcpy(buffer, "end\0");
	send(sockfd, buffer, 20, 0);
	close(sockfd);
	return 0;
}

