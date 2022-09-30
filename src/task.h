#ifndef __TASK_H__
#define __TASK_H__

#include "common.h"
#include "memory_block.h"

#define TASK_PRIORITY_MIN 0
#define TASK_PRIORITY_MAX 10

STRUCT(Task) {
    u64 x[31];
    u64 sp;
    u64 spsr;
    u64 pc;

    u32 tid;
    u32 parent_tid;
    u32 priority;

    MemoryBlock *memory_block;
    Task *next;
};

void task_init(Task* self);

#endif
