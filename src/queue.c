//
// Created by 28379 on 10/4/2022.
//

#include "queue.h"
#include "common.h"
#include "printf.h"

int modular_inc(int x, int mod) {
    return (x + 1) % mod;
}

void init_queue(Queue *queue, u64 *container, int capacity) {
    queue->container = container;
    queue->capacity = capacity;
    queue->head = 0;
    queue->tail = 0;
}

bool is_empty(Queue *queue) {
    return queue->head == queue->tail;
}

bool is_full(Queue *queue) {
    int after_tail = modular_inc(queue->tail, queue->capacity);
    if (queue->head == after_tail) {
        return true;
    } else {
        return false;
    }

}

bool push_queue(Queue *queue, u64 elem) {

    if (is_full(queue)) {
        printf("Queue is full, push_queue fails: (head=%d, tail=%d)\r\n", queue->head, queue->tail);
        return false;
    }

    int new_tail = modular_inc(queue->tail, queue->capacity);
    queue->container[queue->tail] = elem;
    queue->tail = new_tail;
}

u64 pop_queue(Queue *queue) {
    if (is_empty(queue)) {
        return 0;
    }

    u64 result = queue->container[queue->head];
    queue->head = modular_inc(queue->head, queue->capacity);
    return result;
}

