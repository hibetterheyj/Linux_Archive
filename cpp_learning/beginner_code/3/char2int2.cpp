#include<iostream>
#include<stdlib.h>
#include<string>
using namespace std;

//把uchar中的数据还原成int 
void rmethod()
{
	//unsigned char ch[4]={0x00,0x60,0x00,0x08};
	unsigned char ch[2] = {0x00,0x60};
	unsigned int length=0;
	//以下操作完成char型数组到int型的转换
	length=(unsigned int)ch[0] | (unsigned long)ch[1]<<8;
	cout<<length<<endl;
}
 
int main()
{
	rmethod();
	return 0;  
}
