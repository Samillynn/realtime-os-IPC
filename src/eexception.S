.text
.align 4
.global _exception_entry

_exception_entry:

leave_current_task:
    // store x0 to SP, so that x0 can be used temporarily
    str x0, [sp, #-16]!

    // put current task to x0
    ldr x0, =current_task
    ldr x0, [x0]
    add x0, x0, #8

    // save x1 - x30
    stp x1, x2, [x0], #16
    stp x3, x4, [x0], #16
    stp x5, x6, [x0], #16
    stp x7, x8, [x0], #16
    stp x9, x10, [x0], #16
    stp x11, x12, [x0], #16
    stp x13, x14, [x0], #16
    stp x15, x16, [x0], #16
    stp x17, x18, [x0], #16
    stp x19, x20, [x0], #16
    stp x21, x22, [x0], #16
    stp x23, x24, [x0], #16
    stp x25, x26, [x0], #16
    stp x27, x28, [x0], #16
    stp x29, x30, [x0], #16

    // save sp
    msr spsel, #0
    mov x1, sp
    str x1, [x0], #8
    msr spsel, #1

    // str spsr
    mrs x1, spsr_el1
    str x1, [x0], #8

    // str pc
    mrs x1, elr_el1
    str x1, [x0], #8

    // save x0
    ldr x1, [sp], #16
    ldr x0, =current_task
    ldr x0, [x0]
    str x1, [x0]

start_handle_exception:
    mrs x0, esr_el1
    bl handle_exception
    bl schedule


.align 4
.text
.global _enter_current_task
/** @arg current_task **/
/** Context switch back to current_task **/

_enter_current_task:
    ldr x0, =current_task
    ldr x0, [x0]

    // load x1 - x30
    add x0, x0, #8

    ldr x1, [x0], #8
    ldr x2, [x0], #8
    ldr x3, [x0], #8
    ldr x4, [x0], #8
    ldr x5, [x0], #8
    ldr x6, [x0], #8
    ldr x7, [x0], #8
    ldr x8, [x0], #8
    ldr x9, [x0], #8
    ldr x10, [x0], #8
    ldr x11, [x0], #8
    ldr x12, [x0], #8
    ldr x13, [x0], #8
    ldr x14, [x0], #8
    ldr x15, [x0], #8
    ldr x16, [x0], #8
    ldr x17, [x0], #8
    ldr x18, [x0], #8
    ldr x19, [x0], #8
    ldr x20, [x0], #8
    ldr x21, [x0], #8
    ldr x22, [x0], #8
    ldr x23, [x0], #8
    ldr x24, [x0], #8

    ldr x25, [x0], #8
    ldr x26, [x0], #8
    ldr x27, [x0], #8
    ldr x28, [x0], #8
    ldr x29, [x0], #8
    ldr x30, [x0], #8

    // load sp
    msr spsel, #0
    ldr x1, [x0], #8
    mov sp, x1
    msr spsel, #1

    // load spsr
    ldr x1, [x0], #8
    msr spsr_el1, x1

    // load pc
    ldr x1, [x0], #8
    msr elr_el1, x1

    // load x0
    sub x0, x0, #(34*8)
    ldr x0, [x0]

    eret


.global _handle_error
.align 4
_handle_error:
    mrs x0, CurrentEL
    mrs x1, ELR_EL1
    mrs x2, ESR_EL1
    // mrs x3, ELR_EL2
    // mrs x4, ESR_EL2
    // bl print_error
    ret
