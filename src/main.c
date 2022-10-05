#include "syscall.h"
#include "init_kernel.h"
#include "kernel.h"

i32 main() {
    init_kernel();
    kmain();

    return 0;
}
