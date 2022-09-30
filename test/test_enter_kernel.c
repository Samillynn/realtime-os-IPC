//
// Created by 28379 on 9/25/2022.
//

#include "../src/task.h"
#include "../src/exception.h"
#include "../src/syscall.h"
#include "../src/init.h"
#include "../src/kernel.h"
#include "../src/user_tasks.h"

void test_initial_user_task() {
    printf("Enter first user task\r\n\n");
    printf("MyId: %d\r\n\n", MyTid());
    printf("MyParentId: %d\r\n\n", MyParentTid());
    Yield();
    printf("2: Tid: %d, ParentTid: %d\r\n\n", MyTid(), MyParentTid());
    Yield();
    printf("3: Tid: %d, ParentTid: %d\r\n\n", MyTid(), MyParentTid());

    Create(6, demo_user_task);
    printf("Exiting first user task\r\n\n");
}

/* int main() { */
/*     boot(); */
/*     printf("Boot successfully\r\n"); */
/*     handle_error(); */

/*     printf("Start Program\r\n"); */
/*     init(); */
/*     printf("Kernel Program Exit\r\n"); */
/* } */
