//
// Created by 28379 on 9/25/2022.
//

#include "init.h"
#include "kerenel_syscall.h"
#include "user_tasks.h"

void init() {
    init_vector_table();
//    printf("Vector table initialized\r\n");
    init_exception_handlers();
//    printf("Exception handlers initialized\r\n");
    init_first_user_task();
//    printf("Initial user task initialized\r\n");
}

void init_exception_handlers() {
    exception_handlers[1] = sys_create;
    exception_handlers[2] = sys_yield;
    exception_handlers[3] = sys_exit;
    exception_handlers[11] = sys_tid;
    exception_handlers[12] = sys_parent_tid;
}

void init_first_user_task() {
//    printf("Initializing first user task\r\n");
    Task* task = create_task(INITIAL_PRIORITY, initial_user_task, -1);

//    printf("Value of pc: %u\r\n", task->pc);
//    printf("Address of initial_user_task: %u\r\n", initial_user_task);

    // start to run user programs
//    printf("Finish initializing first task\r\n");
    schedule();
}
