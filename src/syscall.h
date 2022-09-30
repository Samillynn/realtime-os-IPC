#ifndef __SYSCALL_H__
#define __SYSCALL_H__

#include "common.h"

extern i32 Create(i32 priority, void (*function)());
extern i32 MyTid();
extern i32 MyParentTid();
extern void Yield();
extern void Exit();

#endif