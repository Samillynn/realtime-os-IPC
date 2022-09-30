#include "task.h"
#include "exception.h"
#include "syscall.h"
#include "init.h"
#include "kernel.h"
#include "user_tasks.h"

i32 main() {
    boot();
    printf("Boot successfully\r\n");
    handle_error();

    printf("Start Program\r\n");
    init();
    printf("Kernel Program Exit\r\n");

    return 0;
}
