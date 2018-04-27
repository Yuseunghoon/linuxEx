#include<stdio.h>

extern inline int square(int x)
{
	return x*x;
}
double add(int x, int y)
{
	return (square(x)+square(y));
}

void main()
{
	int x=2;
	int y=3;
	double result;

	result=add(x,y);

	printf("%lf\n",result);
}
