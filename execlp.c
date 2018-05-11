#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
		printf("Running ps with execlp\n");
		execlp("ps","ps","-ax",(char *)NULL);
		printf("Done\n");
		exit(0);
}
