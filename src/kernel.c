#include "kernel.h"
#include "common.h"
#include "rpi.h"
#include "memory.h"
#include "printf.h"
#include "task_scheduler.h"
#include "exception.h"

void boot() {
    init_gpio();
    init_spi(0);
    init_uart(0);
//    printf("Init I/O\r\n");

    memory_init();
//    printf("Init memory\r\n");
    handle_error();
    task_queue_init();
//    printf("Init task queue\r\n");
    handle_error();
}

void kmain() {
    bool looping = true;

    while (looping) {

    }
}
