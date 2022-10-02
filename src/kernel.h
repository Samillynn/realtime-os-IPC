#ifndef __KERNEL_H__
#define __KERNEL_H__

#include "common.h"
#include "task.h"

extern u64* kernel_regs;
void boot();
void kmain();

#endif
