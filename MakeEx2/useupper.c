#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
	char *filename;
	if(argc != 2){
			fprintf(stderr,"usage: useupper file\n");
			exit(1);
	}
	filename=argv[1];
	if(!freopen(filename,"r",stdin)){
		fprintf(stderr, "could not rediret stdin from file %s\n",filename);
		exit(2);
	}
	execl("./upper","upper",(void *)NULL);
	perror("could not exec ./upper");

}
