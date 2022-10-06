#ifndef __SYSCALL_H__
#define __SYSCALL_H__

#include "common.h"

extern i32 Create(i32 priority, void (*function)());
extern i32 MyTid();
extern i32 MyParentTid();
extern void Yield();
extern void Exit();
extern int Send(int tid, const char *msg, int len_msg, char *reply, int len_reply);
extern int Receive(int *tid, char *msg, int len_msg);
extern int Reply(int tid, const char *reply, int len_reply);

#endif