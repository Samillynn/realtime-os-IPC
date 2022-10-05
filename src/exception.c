//
// Created by 28379 on 9/25/2022.
//
#include "exception.h"
#include "printf.h"

#define EXCEPTION_CLASS_OFFSET 26
#define SVC_CLASS 0x15

u64 (*exception_handlers[1 << 16 ])(void);

u64 activate(Task* task) {
    current_task = task;
    return activate_current_task();
}

void handle_exception(u64 esr) {
    u8 exception_class = (esr >> EXCEPTION_CLASS_OFFSET);
    if (exception_class == SVC_CLASS) {
        u16 imm = esr; // cast to the last 16 bits
        u64 result = exception_handlers[imm]();
        get_current_task()->x[0] = result;
    } else {
        printf("Unsupported exception class: %u\r\n", esr);
    }

    return;
}

void print_error(u64 current_el, u64 elr1, u64 esr1) {
    current_el = (current_el >> 2) & 3;
    printf("CurrentEL is %d\r\n", current_el);
    printf("EL1 - ELR is %x; ESR is %d\r\n", elr1, esr1);
}
