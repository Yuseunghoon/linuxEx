#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define BUFSIZE 50

int main(void)
{	// stdin -> fd=0
	// stdont -> fd=1
	// stderr -> fd=2
	// fd는 3부터 시작

	int fd;
	char temp[50];
	char rbuf[50];
	char lbuf[15]={'\0',};
	char copy[100];
	int wcount;
	int rcount; 
	int pos;

	fd = open("./test.txt",O_RDWR | O_CREAT | O_TRUNC, \
		S_IWUSR | S_IRWXU | S_IXUSR | S_IWGRP); 
	
	if(fd==-1)
	{
		printf("file open error\n");
		return -1;
	}
	
	//버퍼에 테스트 문자열 만들기
	
	sprintf(temp,"Do not count the before that hatch.");
	
	//write(1,temp,strlen(temp)); 
	// text.txt 파일에 문자열 쓰기	
	wcount=write(fd,temp,strlen(temp));
	printf("wcount=%d\n",wcount);
	
	//close(fd);
	//fd=open("./test.txt", O_RDONLY);
	
	//파일내의 커서 위치를 시작점 기준으로 offset 0번지로 이동
	pos=lseek(fd,0,SEEK_SET);
	// lseek(fd, offset, SEEK_END);
	// lseek(fd, offset, SEEK_CUR); 현위치에서 offset 만큼 앞으로

	// lseek로 정상적으로 이동되었는지 확인
	printf("pos=%d\n",pos);
	// 파일 읽기 -> rbuf배열에 채움
	rcount=read(fd,rbuf,BUFSIZE); //BUFSIZE는 받아오는 텍스트 길이 	
	//읽은 문자열 갯수를 확인
	printf("rcount=%d\n",rcount);
	
	// 출력할 내용 : Do not count the eggs before they hatch.
	//읽은 버퍼의 내용 확인
	
	
	printf("rbuf=%s\n",rbuf);
	
	lseek(fd,0,SEEK_SET);
	strncat(copy,rbuf,24);
	strcat(copy,"eggs ");
	lseek(fd,24,SEEK_SET);
	read(fd,lbuf,10);
	strcat(copy, lbuf);

	printf("copy : %s\n",copy);

	//printf("fd=%d\n",fd);
	
	//파일 닫기
	close(fd);
	
	/*
	fd = creat("./test2.txt", 0764); // rwx 111 -> 7, rw0 110 -> 6
	
	if(fd==-1)
	{
		printf("file creat error\n");
		return -1;
	}
	printf("fd=%d\n",fd);
	*/
	return 0;
}
