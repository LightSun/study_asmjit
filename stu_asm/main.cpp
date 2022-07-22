#include <iostream>
#include <stdlib.h>
#include <mmintrin.h>   //mmx
#include <xmmintrin.h>  //sse
#include <emmintrin.h>  //sse2
#include <pmmintrin.h>  //sse3

using namespace std;

int main()
{
    cout << "Hello World!" << endl;
//https://www.cnblogs.com/wangguchangqing/p/5445652.html
    __attribute__((aligned(16)))
    int a[4] = {1,2,3,4}; //要变成2,4,3,1的顺序
    /*
0x2d 就是0010 1101
将从源操作数选择的双字 从左到右，由高到底依次存放在目的操作数
00 选择 1，放在[96-127]
10 选择 3, 放在[64-95]
11 选择 4, 放在[32-63]
01 选择 2, 放在[0-31]
      */
    //below for windows cl compiler
/*
    __asm
    {
        movdqa xmm0,[a];
        pshufd xmm0,xmm0,0x2D; //0010 1101
    };
*/
    //GNU //ERROR not ok
    __asm__
    (
        "movdqa %%xmm0, %0;"  //movdqa
        "pshufd %%xmm0,%%xmm0,0x2D;"
        :       //out "=r"()
        :"r"(a) //input
        :       //result - as register
        //"pshufd %xmm0,%xmm0,0x2D\n\t"
    );
    int s = sizeof(a) /sizeof(a[0]);
    for(int i = 0 ; i < s ; i ++){
        cout << " i = " << i << ", val = " << a[i] << endl;
    }
    return 0;
}
