extern fault_handler

global isr0

isr0:
    cli
    push byte 0
    push byte 0
    jmp isr_common


isr_common:
    pushfq
    push rax
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov rax, rsp
    push rax
    mov rax, fault_handler
    call rax
    pop rax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    add rsp, 8
    popfq
    iretq

