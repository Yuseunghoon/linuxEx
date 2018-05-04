#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char * argv[])
{	
	//argc는 cp, argv1, argv2 3개의 갯수
	//cp 복사할거 복사한 이름 이 3개가 제대로 입력됬는지 파악
	
	//argv1=복사할 이름,argv2=복사한 이름 

	char cp[1000]={'\0'};	
	int fd,ck,end;

	
	fd=open(argv[1],O_RDONLY);

	lseek(fd,0,SEEK_SET);
	end=lseek(fd,0,SEEK_END);
	lseek(fd,0,SEEK_SET);

	read(fd,cp,1000);	
	close(fd);

	printf("log2(read) %s\n",cp);

	fd=open(argv[2], O_RDWR | O_CREAT | O_TRUNC, \
                S_IWUSR | S_IRWXU | S_IXUSR | S_IWGRP); 
	
	if(end>10000000)
		printf("문서가 너무 큽니다.");
	else{
	ck=write(fd,cp,end);
	printf("log3(write) %s\n",cp);
	}
	close(fd);	
	

}
