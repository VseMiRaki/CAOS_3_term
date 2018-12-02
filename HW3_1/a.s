.text
.global classify

snotzeroemaxmnotzero:
    mov    r0, #0x31
    pop    {r4, r5, r6} 
    bx     lr

snotzeroemax:
    cmp    r0, #0
    bne    snotzeroemaxmnotzero
    cmp    r1, #0
    bne    snotzeroemaxmnotzero
    mov    r0, #0xF1
    pop    {r4, r5, r6}
    bx     lr

snotzeroezeromnotzero:
    mov    r0, #0x21
    pop     {r4, r5, r6}
    bx     lr

snotzeroezero:
    cmp    r0, #0
    bne    snotzeroezeromnotzero
    cmp    r1, #0
    bne    snotzeroezeromnotzero
    mov    r0, #0x01
    pop    {r4, r5, r6} 
    bx     lr

szeroemaxmnotzero:
    mov    r0, #0x30
    pop    {r4, r5, r6}
    bx     lr

szeroemax:
    cmp    r0, #0
    bne    szeroemaxmnotzero
    cmp    r1, #0
    bne    szeroemaxmnotzero
    pop    {r4, r5, r6}
    mov    r0, #0xF0
    bx     lr

szeroezeromnotzero:
    mov    r0, #0x20
    pop    {r4, r5, r6}
    bx     lr

szeroezero:
    cmp    r0, #0
    bne    szeroezeromnotzero
    cmp    r1, #0
    bne    szeroezeromnotzero
    mov    r0, #0x00
    pop    {r4, r5, r6}
    bx     lr

szero:
    ldr    r6, =#0x7FF0
    cmp    r5, r6
    beq    szeroemax
    cmp    r5, #0
    beq    szeroezero
    mov    r0, #0x10
    pop    {r4, r5, r6}
    bx     lr

classify:
    push   {r4, r5, r6}
    ldrb   r4, [r0, #7]
    and    r4, #0x80	//S 
    ldrh   r5, [r0, #6]
    ldr    r6, =#0x7FF0
    and    r5, r6  //E
    ldr    r1, [r0]
    ldr    r0, [r0, #4]
    ldr    r6, =#0xFFFFF
    and    r0, r6  //M

    cmp    r4, #0
    beq    szero
    ldr    r6, =#0x7FF0
    cmp    r5, r6
    beq    snotzeroemax
    cmp    r5, #0
    beq    snotzeroezero
    mov    r0, #0x11
    pop    {r4, r5, r6}
    bx     lr
