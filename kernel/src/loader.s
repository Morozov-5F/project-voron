; Copyright (c) 2021, Evgeniy Morozov
; All rights reserved.
; This source code is licensed under the BSD-style license found in the
; LICENSE file in the root directory of this source tree.

global loader
extern kmain        ; Main kernel function

KERNEL_STACK_SIZE equ 4096     ; Kernel stack size
MAGIC_NUMBER equ 0x1BADB002    ; Magic number required for GRUB
FLAGS        equ 0x0           ; Multiboot configuration flags
CHECKSUM     equ -MAGIC_NUMBER ; Checksum (MAGIC_NUMBER + FLAGS + CHECKSUM == 0)

; Setup stack for C programs
section .bss
align 4

kernel_stack: 
    resb KERNEL_STACK_SIZE

; Setup the loader itself
section .text
align 4
    dd MAGIC_NUMBER
    dd FLAGS
    dd CHECKSUM

loader:
    mov esp, kernel_stack + KERNEL_STACK_SIZE ; Point ESP to the start of the stack
    call kmain
    
    mov ebx, 0xDEADBEEF ; Set a special value to the register indicating that kmain is stopped working
    jmp $               ; Loop forever if our kmain exits for some reason