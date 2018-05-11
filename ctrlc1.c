#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

void sigHandler(int sig)
{
	static int count;
	printf("OUCH! - | got signal %d\n",sig);
	count++;
	if(count==5)
		(void) signal(SIGINT, SIG_DFL);
}

int main()
{
	if(signal(SIGINT, sigHandler)==SIG_ERR)
			exit(1);

	while(1)
	{
			printf("HELLO World!\n");
			sleep(1);
	}

}

