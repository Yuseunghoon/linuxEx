#include<stdio.h>
#include<stdlib.h>
#include<string.h>

extern char **environ;

void main()
{
	char strDIR[50];
	char strNAME[50];
	char strResult[100];
	
	//printf("FILEDIR = %s\n",getenv("FILEDIR"));
	//printf("FILENAME = %s\n", getenv("FILENAME"));
	
	sprintf(strDIR,"%s",getenv("FILEDIR"));//sprintf는 strDIR에 FILEDIR 입력
	//printf("%s\n",strDIR);
	sprintf(strNAME,"%s",getenv("FILENAME"));
	//printf("%s\n",strNAME);
	
	sprintf(strResult,"gcc -o txt4 ");
	strcat(strResult,strDIR);//strcat은 문자열 합치는거
	strcat(strResult,strNAME);
	printf("%s\n",strResult);
	//gcc -o txt4 /home/bityu/txt/txt4.c
	system(strResult);
	
	return 0;
}
