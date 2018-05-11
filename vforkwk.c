#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
	int n,s,sum=0,sum_c;
	pid_t pid;
	pid=vfork();

	switch(pid)
	{
		case -1:
			printf("error\n");
			exit(1);
		case 0:
			s=5001;
			break;

		default:
			s=1;
	}

	for(n=0;n<5000;n++)
	{
		sum+=s++;
	}

	if(pid!=0)
		printf("부모 : %d\n",sum);

	else if(pid==0)
	{	
			printf("자식 : %d\n",sum);
			sum_c=sum;
	}

	if(pid!=0)
	{
		printf("부모 + 자식 = %d\n",sum+sum_c);
	}
	sum = 0;
	exit(0);
}
