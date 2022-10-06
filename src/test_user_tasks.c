//
// Created by 28379 on 10/5/2022.
//
#include "syscall.h"
#include "printf.h"
#include "timer.h"

void task_a() {
  printf("Tid of A: %d\r\n", MyTid());
  int tid = 1234;
  printf("*tid = %p\r\n", &tid);
  char a[10];
  int len_msg = Receive(&tid, a, 10);
  printf("Received from %d: %s with length:%d\r\n", tid, a, len_msg);
  char r[] = "bye";
  Reply(tid, r, sizeof r);
}

void task_b() {
  printf("Tid of B: %d\r\n", MyTid());
  char msg[] = "Hello!";
  char reply[10];
  u32 time_a = timer_get_system_time_count();
  int len_reply = Send(1, msg, sizeof msg, reply, 10);
  u32 time_b = timer_get_system_time_count();
  u32 delta_time = time_b - time_a;
  printf("got reply %s with length:%d\r\n", reply, len_reply);

  time_a = timer_get_system_time_count();
  time_b = timer_get_system_time_count();
  delta_time = delta_time - (time_b - time_a);

  printf("Send operation took %dms\r\n", timer_count_to_ms(delta_time));
}

void initial_user_task() {
 printf("start initial user task\r\n");
 i32 tid;

 tid = Create(9, task_a);
 printf("A created\r\n");

 tid = Create(8, task_b);
 printf("B created\r\n");

 Exit();
}
