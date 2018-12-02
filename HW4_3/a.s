.text
.global main

endofinput:
    mov    r6, r5
    sub    r6, #1
    loop1:
        ldr    r0, [r4, r6]
        b      print
        endprint:
        sub    r6, #1
        cmp    r6, #0
        bge    loop1
    b      end

       
end:
    mov    r0, r4
    bl     free
    pop    {r4, r5, r6, lr}
    bx     lr

print:
    ldr    r1, =stdout
    ldr    r1, [r1]
    bl     fputc
    b      endprint

addtoarray:
    mov    r6, r0
    mov    r0, r4
    add    r5, #1
    mov    r1, r5
    bl     realloc
    mov    r4, r0
    mov    r3, r5
    sub    r3, #1
    strb    r6, [r0, r3]
    b      loop

main:
    push   {r4, r5, r6, lr}
    mov    r4, #0
    mov    r0, #0
    mov    r5, #0
    mov    r4, #0
    loop:
        ldr    r0, =stdin
        ldr    r0, [r0]
        bl     fgetc
        cmp    r0, #0
        ble    endofinput
        bl     addtoarray
        b      loop
    pop    {r4, r5, r6, lr}
    bx     lr

        
