; Keyboard ISR routine
; Author: Marcin Jabłoński (TheNNX)

[BITS 64]

[EXTERN keyboard_handler]

[GLOBAL KeyboardIsr]
KeyboardIsr:
    push rax
    push rdi
    push rsi
    push rdx
    push rcx
    push r8
    push r9
    push r10
    push r11
    
    call keyboard_handler
    
    pop r11
    pop r10
    pop r9
    pop r8
    pop rcx
    pop rdx
    pop rsi
    pop rdi
    pop rax
    o64 iret