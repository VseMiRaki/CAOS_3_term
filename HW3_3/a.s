.text


compaire:
    //r1, r2
    ldrb    r4, [r2, #4]
    ldrb    r5, [r3, #4]
    cmp    r4, r5
    bge    compaireend
    ldr    r4, [r2]
    ldr    r5, [r3]
    str    r5, [r2]
    str    r4, [r3]
    add    r2, #4
    add    r3, #4
    ldr    r4, [r2]
    ldr    r5, [r3]
    str    r5, [r2]
    str    r4, [r3]
    add    r2, #4
    add    r3, #4
    ldr    r4, [r2]
    ldr    r5, [r3]
    str    r5, [r2]
    str    r4, [r3]
    add    r2, #4
    add    r3, #4
    ldr    r4, [r2]
    ldr    r5, [r3]
    str    r5, [r2]
    str    r4, [r3]
    add    r2, #4
    add    r3, #4
    ldr    r4, [r2]
    ldr    r5, [r3]
    str    r5, [r2]
    str    r4, [r3]
    add    r2, #4
    add    r3, #4
    ldr    r4, [r2]
    ldr    r5, [r3]
    str    r5, [r2]
    str    r4, [r3]
    add    r2, #4
    add    r3, #4
    ldr    r4, [r2]
    ldr    r5, [r3]
    str    r5, [r2]
    str    r4, [r3]
    add    r2, #4
    add    r3, #4
    ldr    r4, [r2]
    ldr    r5, [r3]
    str    r5, [r2]
    str    r4, [r3]
    add    r2, #4
    add    r3, #4
    ldr    r4, [r2]
    ldr    r5, [r3]
    str    r5, [r2]
    str    r4, [r3]
    add    r2, #4
    add    r3, #4
    ldr    r4, [r2]
    ldr    r5, [r3]
    str    r5, [r2]
    str    r4, [r3]
    add    r2, #4
    add    r3, #4
    ldr    r4, [r2]
    ldr    r5, [r3]
    str    r5, [r2]
    str    r4, [r3]
    add    r2, #4
    add    r3, #4
    ldr    r4, [r2]
    ldr    r5, [r3]
    str    r5, [r2]
    str    r4, [r3]
    add    r2, #4
    add    r3, #4
    b      compaireend

.global sort_by_age
sort_by_age:
    push   {r4-r8}
    mov    r6, #2 //counter for loop1
    mov    r7, r0 //counter for loop2
    loop1:
        mov    r7, r0
        sub    r7, #1
        loop2:
            ldr    r8, =#48
            mov    r2, r7
            mul    r2, r8
            add    r2, r1
            mov    r3, r7
            sub    r3, #1
            mul    r3, r8
            add    r3, r1
            b      compaire
            compaireend:
            cmp    r7, #1
            sub    r7, #1
            bne    loop2
        cmp    r6, r0
        add    r6, #1
        bne    loop1
    pop    {r4-r8}
    bx     lr
