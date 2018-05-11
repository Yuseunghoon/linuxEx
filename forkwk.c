#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
	pid_t pid;
	char *message;
	int s,n,sum;
	int value,status;
	int exit_code;

	printf("cal starting\n");
	pid=fork();


	switch(pid)
	{
		case -1: //error
			perror("fork error");
			exit(1);
		case 0: // child
			s=5000;
			exit_code=17;
			break;

		default:
			s=1;
			exit_code=0;
			break;
	}
	
	for(n=0;n<5000;n++)
	{
		sum+=s++;
	}

	if(pid==0)		  
 		exit(exit_code);

	wait(&status);
	value = WEXITSTATUS(status);

	if(pid!=0)
			printf("parant sum : %d\n",sum);
	else if(pid==0)
			printf("child sum : %d\n",value);
}
