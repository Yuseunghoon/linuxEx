#include <stdio.h>
#include <string.h>
#define DEBUG 1
int main(void){
   int i;
   char strInput[51],charInpu2[51];
   int strSize=0;
   
   //1. 문자열을 입력 받는다.(최대 50문자+NULL문자)
   strSize= scanf("%s",&strInput);
   #ifdef DEBUG
   printf("%d %s \n",strSize,strInput);
   #endif
   //2. 입력받은 문자열이 영문소문자인지 확인한다.
   //   그이외의 입력을 받게 되면 메세지를 출력하고 종료
   strSize = strlen(strInput);
   for(i=0;i<strSize;i++){
      if(!(strInput[i]>='a' && strInput[i]<='z')){
         printf("Error : strInput 옜옜 옜옜.");
         return -1;
      }
   }
   #ifdef DEBUG
   printf("strInput is OK\n");
   #endif
   //3.펠린드롬인지 확인한다.
   #ifdef DEBUG
   if(strSize%2)
      printf("strSize is odd\n");
   else
      printf("strSize is even\n");
   #endif
   for(i=0;i<(strSize>>1);i++){
      if((strInput[i]==strInput[strSize-1-i])){
         printf("strInput is not palindrome \n");
         return -1;
      }
   }
   #ifdef DEBUG
   printf("strInput is palindrome \n");
  #endif
   
   return 0;
}


