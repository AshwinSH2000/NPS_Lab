#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main()
{
	FILE *fp;
	char dataToBeRead[50];
	strcpy(dataToBeRead, "QAZXSWEDCVFRTGBNHYUJMKLIOP");
	fp = fopen("filetoberead.txt","a");
	fputs(dataToBeRead, fp);
	fclose(fp);
	fp = fopen("filetoberead.txt","r");
	if (fp == NULL)
	{
		printf("\nFile does not exist");
		exit(0);
	}
	else
	{
		while( fgets(dataToBeRead, 50, fp)!=NULL)
			printf("%s\n", dataToBeRead);
	}
	fclose(fp);
	return 0;
}
