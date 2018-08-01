#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<string>

void method2()
{
	int a = 10000;
	int b = 10001;
	char s[4];
	s[0]=(char)a;
	s[1]=(char)(a>>8);
	s[2]=(char)b;
	s[3]=(char)(b>>8);
	printf("%x %x %x %x\n",s[0],s[1],s[2],s[3]);
}
int main()
{
	method2();
	return 0;  
}
./

/*用于测试数组接收
#include<stdio.h>
#include<math.h>
#include<cstring>
using namespace std;

int main()
{
 	float a[5];
    a[0]=2.2f;
    a[1]=2.4f;
    a[2]=2.8f;
    a[3]=3.6f;
    a[4]=5.4f;
   	char s[20];
   	float c[5];
    int i=0;
   	memcpy(s, a, sizeof(a));
    for(;i<5;i++)
    {
    	printf("%x %x %x %x\n",s[4i],s[4i+1],s[4i+2],s[4i+3]);
    }
   	
  	// //传输过程
  	// //接收，再转换
   	// memcpy(c, s, sizeof(s));
    // printf("%f\n", c[5]);
	return 0;
}
*/