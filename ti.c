#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define num 10

struct put{
	unsigned char name;
	unsigned char Kor;
	unsigned char Eng;
	unsigned char Math;
	unsigned char Germany;
	short total;
	float average;

};
typedef struct put input;

void main()
{
	input person[num];
	char a[10];
	int i,r;
	
	srand(time(NULL));
	

	for(i=0;i<num;i++)
	{
		person[i].name='a'+i;
		person[i].Kor=(rand()%100);
		person[i].Eng=(rand()%100);
		person[i].Math=(rand()%100);
		person[i].Germany=(rand()%100);
		person[i].total=person[i].Kor+person[i].Eng+person[i].Math+person[i].Germany;
		person[i].average=person[i].total/4;
		
	printf("%c |%d|%d|%d|%d|%d|%f\n",person[i].name,person[i].Kor,person[i].Eng,person[i].Math, person[i].Germany,person[i].total,person[i].average);
	}	
	
}
