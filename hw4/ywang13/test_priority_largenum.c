// Author: Yuxiao Wang
// create a large number of threads in PRIORITY lib, should not crash

#include <stdio.h>
#include <stdlib.h>

#include "userthread.h"

#define THREAD_NUM 10000
#define FAILURE -1

void foo(void* arg) {
}

int main(int argc, char** argv) {
    if (thread_libinit(PRIORITY) == FAILURE) {
        printf("init failure\n");
        exit(EXIT_FAILURE);
    }

    // thread #
    int num[THREAD_NUM];
    for (int i = 0; i < THREAD_NUM; ++i) {
        num[i] = i + 1;
    }

    // create threads
    int threads[THREAD_NUM];
    for (int i = 0; i < THREAD_NUM; ++i) {
        threads[i] = thread_create(foo, num + i, i % 3 - 1);
        if (threads[i] == FAILURE) {
            printf("create failure\n");
            exit(EXIT_FAILURE);
        }
    }

    // join threads
    for (int i = 0; i < THREAD_NUM; ++i) {
        if (thread_join(threads[i]) == FAILURE) {
            printf("join failure\n");
            exit(EXIT_FAILURE);
        }
    }

    if (thread_libterminate() == FAILURE) {
        printf("term failure\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}