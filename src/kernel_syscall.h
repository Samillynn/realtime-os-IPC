#ifndef __KERNEL_SYSCALL_H__
#define __KERNEL_SYSCALL_H__

#include "common.h"

i32 sys_create();
i32 sys_tid();
i32 sys_parentTid();
void sys_yield();
void sys_exit();

#endif
