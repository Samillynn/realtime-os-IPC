//
// Created by 28379 on 9/25/2022.
//

#include "user_tasks.h"
#include "syscall.h"
#include "printf.h"
#include "name_server.h"
#include "rps_server.h"

/* void initial_user_task() { */
/*   printf("start initial user task\r\n"); */
/*   i32 tid; */

/*   tid = Create(9, name_server); */
/*   printf("name server created\r\n"); */
/*   tid = Create(8, rps_server); */
/*   printf("rps server created\r\n"); */

/*   for (usize i = 0; i < 2; i ++) { */
/*     tid = Create(7, rps_client); */
/*     printf("client %lu created\r\n", i); */
/*   } */

/*   Exit(); */
/* } */

