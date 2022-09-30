////
//// Created by 28379 on 9/25/2022.
////
//
//#include "../src/task_scheduler.h"
//#include "utilities.h"
//#include "../src/exception.h"
//
//Task ct_;
//Task* current_task = &ct_;
//
//void task_queue_init();
//void task_queue_add(Task* task);
//
//Task* create_task(u8 priority) {
//    printf("Mock Create task with p=%d, just return the current task\r\n", priority);
//    for (usize i = 0; i < 31; i ++) {
//        current_task->x[i] = i;
//    }
//    current_task->sp = 123;
//    current_task->spsr = 456;
//    current_task->pc = 0;
//
//    printf("Task created is:\r\n");
//    print_task(current_task);
//    printf("address of current task is %d\r\n", (int)current_task);
//    printf("address of x0 is %d\r\n", (int)&current_task->x[0]);
//    printf("address of x1 is %d\r\n", (int)&current_task->x[1]);
//    printf("address of x2 is %d\r\n", (int)&current_task->x[2]);
//    printf("address of x30 is %d\r\n", (int)&current_task->x[30]);
//    printf("address of sp is %d\r\n", (int)&current_task->sp);
//    printf("address of spsr is %d\r\n", (int)&current_task->spsr);
//    printf("address of pc is %d\r\n", (int)&current_task->pc);
//    return current_task;
//}
//
//void remove_current_task(){}
//Task* get_current_task() {
//    printf("Mock get_current_task\r\n");
//    return current_task;
//}
//
//Task* schedule() {
//    printf("Mock Scheduling\r\n");
//    Task* task = get_current_task();
//    printf("Finish get current task in scheduler");
//    print_task(task);
//    enter_current_task();
//}
