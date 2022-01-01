/**
* 测试目标：
*   1. 当越界访问未分配的栈时，是否会报错？
*   2. 当越界访问曾分配但已回收的栈时，是否会报错。
*   3. 当访问已分配的栈时，是否能正常取值。
* 测试方式：
*   1. 目标1直接访问当前内存地址的后1M字节（根据内存页的分配规则，这个页无论如何都不可能已经预分配好了。
*   2. 目标2先递归调用到1M后的字节，然后回到main，再次访问1M后的内存。
*   3. 目标3，多个变量，直接访问当前变量的前N个字节。
* 其它：栈从高地址向低地址增长，线程栈大小为8M。
* 测试结论：
*   1. 将指针向低地址移动，进程占用内存持续增大直到超出栈size(8M)。因此内核未检测栈的越界是基于栈的起始地址到8M。
**/

#include<stdio.h>
#include<string.h>
#include<unistd.h>

static int MEGA_BYTE = 1024 * 1024;
void test_access_not_alloc();
void test_stack_grow();
void test_stack_grow_access();

int main(int argc, char* argv[]) {
    // check argc count and is valid
    if (argc < 2) {
        printf("please select test case.\n");
        return 0;
    }

    if (strcmp(argv[1], "access_not_alloc") == 0) {
        test_access_not_alloc();
    } else if (strcmp(argv[1], "stack_grow") == 0) {
        test_stack_grow();
    } else if (strcmp(argv[1], "stack_grow_access") == 0) {
        test_stack_grow_access();
    }

    return 0;
}

void test_stack_grow() {
    char a = 'a';
    char b = 'b';
    if (&a > &b) {
        printf("stack grow to low addres.\n");
    } else {
        printf("stack grow to high addres.\n");
    }
}

void test_stack_grow_access() {
    char c = 'a';
    char* ptr = &c;

    printf("ptr=%p, ptr[0]=%c\n", ptr, ptr[0]);
    for (int i = 0; i < 1024; ++i) {
        for (int j = 0; j < 50; ++j) { // 1024 / 50 = 21
            ptr = ptr - 4*1024;
            ptr[0] = 'a';
        }
        printf("after grow. ptr=%p, ptr[0]=%c. ptr-st=%ld(Kbyte)\n", ptr, ptr[0], (ptr - &c)/1024);
        sleep(1);
    }
}

void test_access_not_alloc() {
    char c = 0;
    char* ptr = &c;

    printf("ptr=%p, ptr[0]=%c\n", ptr, ptr[0]);
    ptr = ptr - MEGA_BYTE;
    printf("set ptr[0]='a'\n");
    ptr[0] = 'a';
    printf("after set. ptr=%p, ptr[0]=%c\n", ptr, ptr[0]);
}
