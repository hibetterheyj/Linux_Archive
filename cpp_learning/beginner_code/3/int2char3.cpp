#include<iostream>
#include<stdlib.h>
#include<cstring>
#include<stdio.h>
using namespace std;
 
//原理:  使用库函数,拷贝内存; 


void method1()
{
	int a=10000;
	char s[2]={0};
	memcpy(s,&a,sizeof(int));//
	printf("%x %x\n",s[0],s[1]);
}

void method2()
{
	int a = 10000;
	// 转换后应该是10 27
	int b = 10001;
	char s[4];
	s[0]=(char)a;
	s[1]=(char)(a>>8);
	s[2]=(char)b;
	s[3]=(char)(b>>8);
	// 转化为16进制
	printf("%x %x %x %x\n",s[0],s[1],s[2],s[3]);
}

void method3()
{
	int a=255;
	// 转换后应该是ffffffff
	char s[2]; 
	for(int i=0;i<2;i++)  
	{  
		s[i] = *((char*)&a+i);  
	}
	printf("%x %x\n",s[0],s[1]);  
}



int main()
{
	method1();
	return 0;  
}


