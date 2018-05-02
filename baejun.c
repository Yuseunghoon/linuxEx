#include<stdio.h>


int check(int x)
{
	int count=0;

	while(1)
	{
		if(x%2==0)
		{
			count++;
			x/=2;
			
			if(x==0)
			{
				return count;
				break;
			}
		}

		else if(x%2!=0)
		{
			return count;
			break;
		}

		//printf("count = %d\n",count);
	}
}

int check2(int x)
{
	//int r_x=1,r_y=1;
	//printf("%d+%d=%d\n",r_x<<x,r_y<<y,(r_x<<x)+(r_y<<y));

	//r_x=r_x<<x;
	//r_y=r_y<<y;

	//printf("%d+%d=%d\n",r_x,r_y,r_x+r_y);

	int r_x=1;
	return r_x=r_x<<x;	
}

void main()
{
	int x,y,i;
	int r[20]={0,};
	int r_x,r_y;
	int result=0;
		
	printf("숫자 : ");
	scanf("%d %d",&x,&y);
	

	//r_x=check(x);
	//r_y=check(y);

	//printf("before check : %d %d\n",r_x,r_y);

	for(i=0;i<y-x+1;i++)
	{
		r[i]=check2(check(x+i));
		//printf("%d\n",r[i]);
		result+=r[i];
	}

	//for(i=0;i<y-x;i++)
	//{
	//	result+=r[i];
	//}
	//check2(r_x,r_y);

	printf("%d\n",result);	
}
