#include <stdio.h>

int main(void)
{
	int i;
	char strInput[51];
	int strSize;
	
	scanf("%s",strInput);

#ifdef DEBUG
	printf("%s\n",strInput);
#endif
	
	for(i=0;i<strlen(strInput);i++)
	{
		if(strInput[i]>= && strInput[i]<='z')
		printf("Error : 소문자가 아닙니다.");
			
	}

}
