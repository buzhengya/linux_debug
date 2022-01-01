/**
* 测试目标：
*   1. 当越界访问未分配的堆时，是否会报错？
* 测试方式：
*   1. 目标1直接访问当前堆内存地址，然后逐步增加直到提示越界（根据内存的分配规则，按页分配，初始内存是已分配的，超出一页后报错）。
* 其它：堆从低地址向高地址增长，页大小为4K。
* 测试结论：
*   1. 将指针向高地址移动，直到超出当前堆内存页的边界，在mac上的测试结果为超出224Kbyte不到256Kbyte时段错误。
**/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

static int MEGA_BYTE = 1024 * 1024;
void test_access_not_alloc();
void test_heap_grow();
void test_heap_grow_access();

int main(int argc, char* argv[]) {
    // check argc count and is valid
    if (argc < 2) {
        printf("please select test case.\n");
        return 0;
    }

    if (strcmp(argv[1], "access_not_alloc") == 0) {
        test_access_not_alloc();
    } else if (strcmp(argv[1], "heap_grow") == 0) {
        test_heap_grow();
    } else if (strcmp(argv[1], "heap_grow_access") == 0) {
        test_heap_grow_access();
    }

    return 0;
}

void test_heap_grow() {
    int* a = malloc(sizeof(int));
    int* b = malloc(sizeof(int));
    if (a > b) {
        printf("heap grow to low addres.\n");
    } else {
        printf("heap grow to high addres.\n");
    }
}

void test_heap_grow_access() {
    int* c = malloc(sizeof(int));
    int* ptr = c;

    printf("ptr=%p, ptr[0]=%d\n", ptr, ptr[0]);
    for (int i = 0; i < 1024; ++i) {
        for (int j = 0; j < 8*1024; ++j) { // 4 * 1024 / (128 * 4) = 8
            ptr = ptr + 4;
            ptr[0] = 1;
        }
        printf("after grow. ptr=%p, ptr[0]=%d. ptr-st=%ld(Kbyte)\n", ptr, ptr[0], (ptr - c)/ 1024);
        sleep(1);
    }
}

void test_access_not_alloc() {
    int* a = malloc(sizeof(int));
    int* ptr = a;

    // printf("ptr=%p, ptr[0]=%d\n", ptr, ptr[0]);
    ptr = ptr + 100*4;
    // printf("set ptr[0]=1\n");
    ptr[0] = 1;
    // printf("after set. ptr=%p, ptr[0]=%d\n", ptr, ptr[0]);
    printf("ptr-a=%ld, access out of bounds success.\n", ptr - a);
}
