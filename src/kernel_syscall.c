#include "kernel_syscall.h"
#include "task.h"
#include "task_scheduler.h"
#include "../test/utilities.h"
#include "printf.h"

/** Create a user task by a user task **/
i32 sys_create() {
    Task *current_task = get_current_task();

    if (current_task != NULL) {
        int priority = current_task->x[0];
        u64 func_ptr = current_task->x[1];
        Task *new_task = create_task(priority, func_ptr, current_task->tid);
        if(new_task != NULL) {
            return new_task->tid;
        } else {
            return -1;
        }
    }

    return -1;
}

i32 sys_tid() {
    Task *current_task = get_current_task();

//    printf("Check current_task in TID call\r\n");
    if (current_task) {
        print_current_task();
        return current_task->tid;
    } else {
//        printf("Current task is NULL\r\n");
        return -1;
    }

}

i32 sys_parent_tid() {
    Task *current_task = get_current_task();
//    printf("Check current_task in ParentTID call\r\n");

    if (current_task) {
        print_current_task();
        return current_task->parent_tid;
    } else {
        printf("Current task is NULL\r\n");
        return -1;
    }
}

void sys_yield() {
//    printf("The following task is yielding\r\n");
    print_current_task();
    // do nothing
}

void sys_exit() {
    remove_current_task();
}


