//
// Created by 28379 on 9/25/2022.
//

.text
.align 4
.global Create
Create:
    svc #1
    ret


.text
.align 4
.global Yield
Yield:
    svc #2
    ret

.text
.align 4
.global Exit
Exit:
    svc #3
    ret

.text
.align 4
.global MyTid
MyTid:
    svc #11
    ret

.text
.align 4
.global MyParentTid
MyParentTid:
    svc #12
    ret
