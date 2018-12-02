.text
.global check_int

zero:
    mov    r0, #1
    bx     lr

check_int:
    cmp    r0, #0
    beq    zero
    mov    r1, #0 // Счетчик для нулей справа
    mov    r2, #0 // Счетчик для нулей слева
    push   {r4}
    mov    r3, #1
    rightloop:
        and    r4, r0, r3
        cmp    r4, #0
        add    r1, #1
        mov    r3, r3, lsl #1
        beq    rightloop
    sub    r1, #1
    ldr    r3, =#0x80000000
    leftloop:
        and    r4, r0, r3
        mov    r3, r3, lsr #1
        add    r2, #1
        cmp    r4, #0
        beq    leftloop
    sub    r2, #1   
    add    r3, r2, #32
    sub    r3, r2
    sub    r3, r2
    mov    r2, r3
    sub    r2, r1
    cmp    r2, #24
    mov    r0, #1
    pop    {r4}
    bxle   lr
    mov    r0, #0
    bx     lr
