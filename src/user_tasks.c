//
// Created by 28379 on 9/25/2022.
//

#include "user_tasks.h"
#include "syscall.h"
#include "printf.h"

void initial_user_task() {
    int priorities[4] = {INITIAL_PRIORITY - 2, INITIAL_PRIORITY - 1, INITIAL_PRIORITY + 1, INITIAL_PRIORITY + 2};
    for (int i = 0; i < 4; i++) {
        int tid = Create(priorities[i], demo_user_task);
        printf("Created: %d\r\n\n", tid);
    }
    printf("FirstUserTask: exiting\r\n\n");
    Exit();
}

void demo_user_task() {
    printf("Tid: %d, ParentTid: %d\r\n\n", MyTid(), MyParentTid());
    Yield();
    printf("Tid: %d, ParentTid: %d\r\n\n", MyTid(), MyParentTid());
    Exit();
}