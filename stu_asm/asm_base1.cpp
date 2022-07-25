#include <stdlib.h>
#include <stdio.h>

int fn(int a, int b){
    int rsp_move = 4;
    int c = a + b;
    return c;
}
/*
fn(int, int):
        pushq   %rbp
        movq    %rsp, %rbp
        movl    %edi, -20(%rbp)
        movl    %esi, -24(%rbp)
        movl    $4, -4(%rbp)
        movl    -20(%rbp), %edx
        movl    -24(%rbp), %eax
        addl    %edx, %eax
        movl    %eax, -8(%rbp)
        movl    -8(%rbp), %eax
        popq    %rbp
        ret
*/

struct Stu{
    int age;
    char* name;
};

void test_malloc_free(){
    Stu* a = (Stu*)malloc(sizeof(Stu));
    printf("name = %s\n", a->name);
   // printf("age = %d\n", a->age);
    free(a);
}

void test1(Stu stu){
    printf("name = %s\n", stu.name);
}
/*
test1(Stu):
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $16, %rsp

        movl    %edi, %eax # 'stu' -> eax
        movq    %rsi, %rcx  # 取高64位（8字节）值
        movq    %rcx, %rdx //???
        movq    %rax, -16(%rbp)
        movq    %rdx, -8(%rbp)

        movq    -8(%rbp), %rax
        movq    %rax, %rsi
        movl    $.LC0, %edi
        movl    $0, %eax
        call    printf
        nop
        leave
        ret
*/

/*
.LC0:
        .string "name = %s\n"
test_malloc_free():
        pushq   %rbp
        movq    %rsp, %rbp

        subq    $16, %rsp
        movl    $16, %edi
        call    malloc

        movq    %rax, -8(%rbp) #malloc返回值 放到rbp-8

        movq    -8(%rbp), %rax
        movq    8(%rax), %rax
        movq    %rax, %rsi
        movl    $.LC0, %edi
        movl    $0, %eax
        call    printf

        movq    -8(%rbp), %rax
        movq    %rax, %rdi
        call    free
        nop
        leave
        ret
*/

void test(Stu& stu){
    printf("name = %s\n", stu.name);
    printf("age = %d\n", stu.age);
}
/*
.LC0:
        .string "name = %s\n"
.LC1:
        .string "age = %d\n"
test(Stu&):
        pushq   %rbp          # 保存旧的帧指针，相当于创建新的栈帧部
        movq    %rsp, %rbp  # 让 %rbp 指向新栈帧的起始位置
        subq    $16, %rsp   # 在新栈帧中预留一些空位，供子程序使用，
                              //用 (%rsp+K) 或 (%rbp-K) 的形式引用空位

        movq    %rdi, -8(%rbp) //rdi 字符串目的地址
        movq    -8(%rbp), %rax //从rbp-8处取出值存放在rax寄存器中
        movq    8(%rax), %rax
        movq    %rax, %rsi  // rsi字符串操作时，用于存放数据源的地址
        movl    $.LC0, %edi // movl 寄存器是目的
        movl    $0, %eax
        call    printf

        movq    -8(%rbp), %rax
        movl    (%rax), %eax
        movl    %eax, %esi
        movl    $.LC1, %edi
        movl    $0, %eax
        call    printf

        nop
        leave
        ret
 */

/*
eax(rax): 通常用来执行加法，函数调用的返回值一般也放在这里面
ebx(rbx): 数据存取
ecx(rcx): 通常用来作为计数器，比如for循环
edx(rdx): 读写I/O端口时，edx用来存放端口号
esp(rsp): 堆栈指针寄存器，指向栈的顶部
ebp(rbp): 栈帧指针，指向栈的底部，通常用ebp+偏移量的形式来定位函数存放在栈中的局部变量
          //%rbp 是栈帧指针，用于标识当前栈帧的起始位置
esi(rsi): 字符串操作时，用于存放数据源的地址
edi(rdi): 字符串操作时，用于存放目的地址的，和esi两个经常搭配一起使用，执行字符串的复制等操作
*/
