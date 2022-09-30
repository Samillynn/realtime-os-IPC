//
// Created by 28379 on 9/25/2022.
//
#include "exception.h"
#include "printf.h"

#define EXCEPTION_CLASS_OFFSET 26
#define SVC_CLASS 0x15

u64 (*exception_handlers[1 << 16 ])(void);

void handle_exception(u64 esr) {
//    printf("Calling Handle Exception\r\n");
//    printf("Exception code is %u\r\n", esr);
    u8 exception_class = (esr >> EXCEPTION_CLASS_OFFSET);
    if (exception_class == SVC_CLASS) {
        u16 imm = esr; // cast to the last 16 bits
        u64 result = exception_handlers[imm]();
//        printf("Kernel returned result for SVC(%d) is %u\r\n", imm, result);
        get_current_task()->x[0] = result;
    } else {
        printf("Unsupported exception class: %u\r\n", esr);
    }

//    printf("Exit handle_exception\r\n");
    return;
}
