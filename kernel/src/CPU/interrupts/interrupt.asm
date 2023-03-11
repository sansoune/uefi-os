global isr0
extern ISR0_Handler

section .text

isr0:
    push 0                      ; Push error code
    push 0                      ; Push interrupt number
    call ISR0_Handler            ; Call interrupt handler
    add  rsp, 8                 ; Restore stack pointer
    iretq                       ; Return from interrupt