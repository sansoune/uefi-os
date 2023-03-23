[BITS 64]
%macro pushaq 0
    push rax      ;save current rax
    push rbx      ;save current rbx
    push rcx      ;save current rcx
    push rdx      ;save current rdx
    push rbp      ;save current rbp
    push rdi       ;save current rdi
    push rsi       ;save current rsi
    push r8        ;save current r8
    push r9        ;save current r9
    push r10      ;save current r10
    push r11      ;save current r11
    push r12      ;save current r12
    push r13      ;save current r13
    push r14      ;save current r14
    push r15      ;save current r15
%endmacro

%macro popaq 0
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rsi
    pop rdi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax
%endmacro

%macro ISR_NOERRORCODE 1

global isr%1:
isr%1:
    cli
    cld
    push 0              ; push dummy error code
    push %1             ; push interrupt number
    jmp isr_common

%endmacro

%macro ISR_ERRORCODE 1
global isr%1:
isr%1:
    cli                    ; cpu pushes an error code to the stack
    push %1             ; push interrupt number
    jmp isr_common

%endmacro

ISR_NOERRORCODE 0
ISR_ERRORCODE 14

extern isr_handler
isr_common:
    push rbp
    mov rbp, rsp
    pushaq
    
    mov eax, [rbp+32]
    mov [rsp + 32], eax
    mov rsi, [rbp + 8]
    call isr_handler
    
    popaq
    mov rsp, rbp
    pop rbp
    o64 iret