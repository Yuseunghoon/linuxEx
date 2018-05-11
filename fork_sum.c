#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main(void)
{
	pid_t pid;
	int sum = 0;
	int temp;
	int s_num, e_num;

	pid = fork();

	switch(pid)
	{
			case -1:
				perror("fork failed");
				exit(1);
			case 0:
				s_num = 1;
				e_num = 5;
				break;
			default:
				s_num = 6;
				e_num = 10;
	}
	
	for(int i = s_num; i <= e_num; i++)
			sum += i;

	if(pid != 0)
	{
		wait(&temp);

		if(WIFEXITED(temp))
			printf("자식 정상종료 : %d\n", WEXITSTATUS(temp));
		else if(WIFSIGNALED(temp))
			printf("자식 비정상 종료 : %d\n", WTERMSIG(temp));
		else
			printf("자식 멈춤 : %d\n", WSTOPSIG(temp));
		printf("부모 합 : %d\n", sum);
		printf("자식 부모 합 : %d", WEXITSTATUS(temp) + sum);
	}
	else
	{
		printf("자식아 : %d\n", pid);
		//exit(1);
		printf("자식 합 : %d\n", sum);
	}
	exit(sum);
}
