#include<stdio.h>
#include<string.h>
#include<stdlib.h>



void main()
{
	int max;
	int a[10][10];//=(int *)malloc(max*sizeof(int));
	int size=0;//max;
	int x=0,y=-1;
	int data=0;
	int sw=1;
	int i,j;

	printf("put size = ");
	scanf("%d",&max);

	//*a=(int *)malloc(max*sizeof(int));
	size = max;

	while(1)
	{

		for(i=0;i<size;i++)
		{
			y+=sw;
			a[x][y]=data++;
		}

		size--;

		if(size<0) break;

		for(i=0;i<size;i++)
		{
			x+=sw;
			a[x][y]=data++;
		}

		sw=-sw;

	}

	for(i=0;i<max;i++){
		for(j=0;j<max;j++)
			printf("|%2d|",a[i][j]);

		printf("\n");
	}


}
