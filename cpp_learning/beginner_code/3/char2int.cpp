
#include <stdio.h>
#include <cstring>
typedef unsigned char uchar;
typedef unsigned int  uint;
//转换函数
//Temp 字符型数组
//pOut int型数组
//length 字符型数组的长度
//这里假设字符型数组里包含的都是偶数个元素
//如果是奇数个数，则需要增加如下处理：
//检查length是否是奇数，如果是，动态分配length+1个char大小的数组
//数据全部清零，并且把Temp的内容拷贝到动态分配的数组中
//按照下面长度是偶数的情况处理
//释放动态分配的内存
//这里根据问题要求，应该是以小端序来存放int类型的
//如果更智能一些，可以写一个检查字节序的函数来处理
void Exchange(const uchar *Temp, uint *pOut, uchar length)
{
    int i = 0;
    for (; i < length / 2; i++)
    {
        //小端序，直接按原来的顺序拷贝过去
        //如果是大端序，则可以改变一下字节序
        memcpy(pOut, Temp, 2);
        pOut++;//int型指针后移一位
        Temp+=2;//字符型字节后移两位    
    }
}
//测试代码
int main(void)
{
    int i;
    uint array[20] = {0};
    uchar Start[] = {0x80,0xF1,0x58,0x03,0xC1,0xEA,0x8F,0x06};
    Exchange(Start, array, sizeof(Start));
    for (i = 0; i < 20; i++)
    {
        if (array[i] != 0)
        {
            printf("0x%04X ", array[i]);
        }        
    }    
    printf("\n");
    return 0;
}
