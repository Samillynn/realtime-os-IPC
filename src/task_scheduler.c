#include "task_scheduler.h"
#include "memory.h"
#include "utilities.h"
#include "syscall.h"
#include "exception.h"
#include "printf.h"
#include "boot.h"
#include "../test/utilities.h"

#define TASK_POOL_SIZE  64

#define SPSR_MASK_ALL (7 << 6)
#define SPSR_EL1h (5 << 0)
#define SPSR_VALUE (SPSR_MASK_ALL | SPSR_EL1h)

static Task task_pool[TASK_POOL_SIZE];
static Task *task_pool_ptr;
static TaskQueue task_queue[TASK_PRIORITY_MAX];

static i32 task_id_cnt;

Task *current_task;

void task_queue_init() {
    current_task = NULL;

    for (usize i = 0; i < TASK_POOL_SIZE; i++) {
        task_init(&task_pool[i]);
        if (i < TASK_POOL_SIZE - 1) {
            task_pool[i].next = &task_pool[i + 1];
        } else {
            task_pool[i].next = NULL;
        }
    }

    for (usize i = TASK_PRIORITY_MIN; i < TASK_PRIORITY_MAX; i++) {
        task_queue[i].front = NULL;
        task_queue[i].end = NULL;
    }

    task_pool_ptr = &task_pool[0];

    task_id_cnt = 0;
}

void task_queue_add(Task *task) {
//    printf("Calling task_queue_add\r\n");
    i32 priority = task->priority;

    if (task_queue[priority].end) {
        task_queue[priority].end->next = task;
        task_queue[priority].end = task_queue[priority].end->next;
    } else {
        task_queue[priority].end = task;
        task_queue[priority].front = task;
    }

    task->next = NULL;
//    printf("Finish task_queue_add\r\n");
}

Task *task_queue_pop() {
    Task *popped = NULL;

    for (i32 i = TASK_PRIORITY_MAX - 1; i >= TASK_PRIORITY_MIN; i--) {
        if (task_queue[i].front) {
            popped = task_queue[i].front;
            if (task_queue[i].front->next) {
                task_queue[i].front = task_queue[i].front->next;
            } else {
                task_queue[i].front = NULL;
                task_queue[i].end = NULL;
            }
            break;
        }
    }

    return popped;
}

Task *task_queue_peek() {
    Task *task = NULL;

    for (i32 i = TASK_PRIORITY_MAX - 1; i >= TASK_PRIORITY_MIN; i--) {
        if (task_queue[i].front) {
            task = task_queue[i].front;
            break;
        }
    }

    return task;
}

char stack[10000];
Task *create_task(i32 priority, void (*func)(), i32 parent_tid) {
    priority = i32_clamp(priority, TASK_PRIORITY_MIN, TASK_PRIORITY_MAX - 1);
    Task *task = NULL;
//    printf("Calling create_task\r\n");

    if (task_pool_ptr) { // TODO: check priority range
//        printf("task_pool_ptr = %p\r\n", task_pool_ptr);
        task = task_pool_ptr;
        task_pool_ptr = task->next;
        task_init(task);

        task->tid = task_id_cnt;
        task_id_cnt += 1;
        task->parent_tid = parent_tid;
        task->priority = priority;

        // TODO: ask Daniel, swap the next 2 statements
        task->memory_block = memory_allocate_block();
//        task->sp = task->memory_block->address;
        task->sp = (u64)memory_get_block_end(task->memory_block);

        task->pc = (u64)func;
        task->x[30] = (u64)Exit;

        task->spsr = 0;

        task->next = NULL;

        task_queue_add(task);
//        printf("Task created successfully: tid=%d, pid=%d, pty=%d\r\n\n", task->tid, task->parent_tid, task->priority);
    } else {
        printf("Task creating failed\r\n");
    }
//    printf("------------------------------\r\n");

    return task;
}

void remove_current_task() {
    memory_free_block(current_task->memory_block);

    task_init(current_task);
    current_task = NULL;
}

Task *get_current_task() {
    return current_task;
}

Task *schedule() {
//    printf("Calling schedule\r\n");
    if (current_task) {
        task_queue_add(current_task);
    }

    current_task = task_queue_pop();
    if (get_current_task() != NULL) {
//        printf("The newly scheduled task is\r\n");
        print_current_task();
//        printf("Enter current task, aka. context switch\r\n");
//        printf("------------------------------\r\n");
        enter_current_task();
    } else {
        printf("All user tasks have finished, exit elegantly\r\n");
        exit_all();
    }
    return current_task;
}
