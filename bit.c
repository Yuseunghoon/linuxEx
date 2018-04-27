#include<stdio.h>

struct Flags{
	unsigned int a : 1;
	unsigned int b : 3;
	unsigned int c : 7;
};

struct Flags2{
	unsigned int a : 1;
        unsigned int b : 3;
        unsigned int c : 31;
};

int main()
{
	struct Flags f1;
	struct Flags2 f2;

	f1.a=1;
	f1.b=15;
	f1.c=255;

	printf("%d\n",f1.a);
	printf("%d\n",f1.b);
	printf("%d\n",f1.c);
	
	printf("%d\n",sizeof(f1));
	printf("%d\n",sizeof(f2));
	return 0;
}
