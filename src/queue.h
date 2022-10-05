//
// Created by 28379 on 10/4/2022.
//

#ifndef K2_QUEUE_H
#define K2_QUEUE_H
#include "common.h"

STRUCT(Queue) {
        u64 *container;
        int capacity;
        int size;
        int head;
        int tail;
};

void init_queue(Queue *queue, u64 *container, int capacity);
bool is_empty(Queue *queue);
bool push_queue(Queue *queue, u64 elem);
u64 pop_queue(Queue *queue);

#endif //K2_QUEUE_H
