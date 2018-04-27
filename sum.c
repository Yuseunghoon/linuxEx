#include <stdio.h>
#define MUL2(x,y) ((x)*(y))


void main()
{
	int a=1, b=2,c=3,d=4,k=0;
	k=MUL2(a+b,c+d);
	printf("%d\n",k);
}
