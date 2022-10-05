//
// Created by 28379 on 10/5/2022.
//

#include "../src/queue.h"
#include "print.h"

int main() {
    u64 _queue[10];
    Queue queue;
    init_queue(&queue, _queue, 10);

    push_queue(&queue, 1);
    push_queue(&queue, 2);
    push_queue(&queue, 3);
    printf_("head=%d, tail=%d\n", queue.head, queue.tail);

    int x = pop_queue(&queue);
    int y = pop_queue(&queue);
    int z = pop_queue(&queue);

    printf_("x=%d,y=%d,z=%d\n", x, y, z);
    printf_("head=%d, tail=%d\n", queue.head, queue.tail);

    int should_be_zero = pop_queue(&queue);
    printf_("this should be zero: %d\n", should_be_zero);
    printf_("head=%d, tail=%d\n", queue.head, queue.tail);
}
