/**
 * test is thread map one pid and task_struct.
 **/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// 线程一
void thread_func(void) {
    sleep(3);
    pid_t pid = getpid();
    pthread_t tid = pthread_self();
    printf("print current thread. pid : %d, tid: %d\n", pid, (unsigned int)tid);
    sleep(60 * 1000);
}

const int THREAD_NUM = 128;

int main(void) {
    pthread_t tid;
    int ret;

    /*创建线程一*/
    for (int i = 0; i < THREAD_NUM; ++i) {
        ret = pthread_create(&tid, NULL, (void  *) thread_func, NULL);
        if(ret != 0) {
            printf("Create pthread error! ret : %d\n", ret);
            return -1;
        } else {
            printf("Create pthread success. tid : %d\n", (unsigned int)tid);
        }
    }


    /*等待线程结束*/
    pthread_join(tid, NULL);
    return 0;
}