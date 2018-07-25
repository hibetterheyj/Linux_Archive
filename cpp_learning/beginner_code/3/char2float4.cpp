#include<stdio.h>
#include<math.h>
#include<cstring>
using namespace std;

int main()
{
 	float a = 2.2f;
   	char s[4];
   	float c;
   	memcpy(s, &a, sizeof(a));
 	printf("%x %x %x %x\n",s[0],s[1],s[2],s[3]);
   	
  	//传输过程
  	//接收，再转换
   	memcpy(&c, s, sizeof(s));
    	printf("%f\n", c);
	return 0;
}