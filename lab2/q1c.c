#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>

int main()
{
	int sfd;
	sfd = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(1435);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(&(server.sin_zero), '\0', sizeof(server.sin_zero));
	
	char filename[20];
	int result;
	int size = sizeof(struct sockaddr);
	connect(sfd, (struct sockaddr *)& server, size);
	printf("\nEnter the file name:");
	scanf("%s",filename);
	send(sfd, filename, sizeof(filename), 0);
	recv(sfd, &result, sizeof(result), 0);
	if(!result)
	{
		printf("\nFile not present");
		close(sfd);
		exit(0);
	}
	printf("\n1. Search\n2. Replace\n3. Reorder\n4. Exit\nEnter your choice:");
	int ch;
	scanf("%d", &ch);
	//have to choose bw 4 options
	send(sfd, &ch, sizeof(ch), 0);
	char str[10];
	int count;
	switch(ch)
	{
		case 1:printf("\nEnter the string to be searched:");
				scanf("%s",str);
				send(sfd, str, sizeof(str), 0);
				recv(sfd, &count, sizeof(count), 0);
				if(!count)
					printf("\nString not found");
				else
					printf("%s found %d times in the %s", str, count, filename);
				break;
		/*case 2:printf("\nEnter the string to be searched:");
				scanf("%s",str);
				send(sfd, str, sizeof(str), 0);*/
	}
	
	close(sfd);
	return 0;	
}
