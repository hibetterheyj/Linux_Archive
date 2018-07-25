#include<stdio.h>
#include<math.h>
#include<cstring>
using namespace std;

void float2char()
{
	float a=1.1;
	// ffffffcd ffffffcc ffffff8c 3f
	char s[4]={0};
	memcpy(s,&a,sizeof(float));//
	printf("%x %x %x %x\n",s[0],s[1],s[2],s[3]);
}

int main()
{
 	// float a[2];
	// a[1] = 1254.42f;
	// a[2] = 1.1;
   	// char s[8];
   	// float c;
   	// memcpy(s, &a, sizeof(a));
 	// printf("%x %x %x %x\n",s[0],s[1],s[2],s[3]);
   	
  	// //传输过程
  	// //接收，再转换
   	// memcpy(&c, s, sizeof(s));
    // 	printf("%f\n", c);
	float2char();
	return 0;
}