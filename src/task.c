#include "task.h"
#include "printf.h"

void task_init(Task *self) {
    self->tid = -1;
    self->parent_tid = -1;
    self->priority = TASK_PRIORITY_MIN;

    for (usize i = 0; i < 31; i++) {
        self->x[i] = 0;
    }
    self->sp = 0;
    self->spsr = 0;
    self->pc = 0;

    self->memory_block = NULL;
    self->next = NULL;
}
