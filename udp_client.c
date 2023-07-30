#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
 
#define myport 3453

int main()
{
	int sockfd;
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	struct sockaddr_in dest_addr;
	
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(myport);
	dest_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset( &(dest_addr.sin_zero), '\0', sizeof(dest_addr.sin_zero));
	
	socklen_t size = sizeof(struct sockaddr );
	char buffer[20] = "hello udp!";
	
	//sending the data
	sendto(sockfd, buffer, 20, 0, (struct sockaddr *) &dest_addr, size);
	
	//echoed reply from server
	char buffer2[20];
	recvfrom(sockfd, buffer2, 20,0, (struct sockaddr *) &dest_addr, &size);
	printf("\nEchoed data = %s\n", buffer2);
	//closing the socket
	close(sockfd);
	return 0;
}
