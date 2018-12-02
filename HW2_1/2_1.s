.text
.global summ
summ:
push {r4, r5}
mov r4, #0  //counter
.loop:
ldr r5, [r2]
add r0, r5
add r2, #4
add r4, #1
cmp r4, r1
bne .loop
mov r1, r0
pop {r4, r5}
bx lr
