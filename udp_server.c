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
	struct sockaddr_in server_addr, client_addr;
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(myport);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //this has to do something with the localhost
	memset( &(server_addr.sin_zero), '\0', sizeof(server_addr.sin_zero));
	
	bind(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
	
	//there is not listen and accept function calls in udp program. it directly reveives contents using receivefrom()
	printf("server is ready to receive\n");
	socklen_t size;
	size = sizeof(struct sockaddr );
	char buffer[20];
	recvfrom(sockfd, buffer, 20, 0, (struct sockaddr *)&client_addr, &size);
	printf("\nReceived data = %s\n", buffer);
	sendto(sockfd, buffer, 20, 0, (struct sockaddr *)&client_addr, size);
	close(sockfd);
	return 0;
}
