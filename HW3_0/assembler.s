    .text
    .global calculate
calculate:
ldrb r1, [r0]
ldrsh r2, [r0, #2]
ldr r3, [r0, #4]
add r2, r1
adds r2, r3
mov r0, r2
mov r1, #0
adc r1, #0
bx lr


