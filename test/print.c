//
// Created by 28379 on 10/5/2022.
//

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "../src/task.h"
#include "../src/message_passing.h"


void printf_( const char* format, ... )
{
    va_list arglist;

    va_start( arglist, format );
    vprintf( format, arglist );
    va_end( arglist );
}

void print_task(Task* t) {
    for(int i = 0; i < 8; i++) {
        printf_("x[%d] = %llu\r\n", i, t->x[i]);
    }
    printf_("tid = %d\r\n", t->tid);
}

void print_send(SendArgs* send) {
    printf_("tid=%d, msg=%s, msg_len=%d, reply=%s, reply_len=%d\r\n", send->tid, send->msg, send->msg_len, send->reply, send->reply_len);
}

void print_receive(ReceiveArgs* receive) {
    printf_("length/tid=%d, msg=%s, msg_len=%d\r\n", receive->tid, receive->msg, receive->msg_len);
}