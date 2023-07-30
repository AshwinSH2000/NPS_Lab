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
	struct sockaddr_in server, client;
	server.sin_family = AF_INET;
	server.sin_port = htons(1435);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	memset(&(server.sin_zero), '\0', sizeof(server.sin_zero));
	
	bind(sfd, (struct sockaddr *)&server, sizeof(server));
//	printf("\nlistening");
	listen(sfd, 1);
	int size = sizeof(struct sockaddr);
	int afd = accept(sfd, (struct sockaddr *)& client, &size);
	char filename[20], str[10], toberead[100];
	int result, ch;	
	recv(afd, filename, sizeof(filename), 0);
	FILE *fp;
	fp = fopen(filename, "r");
	if(fp==NULL)
	{	result = 0;
		send(afd, &result, sizeof(result), 0);
		close(fp);
		close(sfd);
		exit(0);
	}
	close(fp);
	result = 1;
	send(afd, &result, sizeof(result), 0);
	recv(sfd, &ch, sizeof(result), 0);
	switch(ch)
	{
		case 1:recv(afd, str, sizeof(str), 0);
				fp = fopen(filename, "r");
				int count = 0;
				while( fgets(toberead, 100, fp)!=NULL )
					count += search(toberead, str);
				send(afd, &count, sizeof(result), 0);
				fclose(fp);
				break;

				
				
		
	}
	close(sfd);
	return 0;	
}
