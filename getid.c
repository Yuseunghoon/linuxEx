#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
	pid_t pid;

	sleep(5);
	printf("\nProcess ID            = %d\n",pid = getpid());
	printf("Parent process ID       = %d\n",getppid());
	printf("Reel User ID            = %d\n",geteuid());
	printf("Reel group ID           = %d\n",getgid());
	printf("Effective group ID      = %d\n",getegid());
}
