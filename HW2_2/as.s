    .text
    .global solve
solve:
push {r4-r10}
mov r4, #0
mov r6, r0
mov r7, r1
mov r8, r2
mov r9, r3

loop:
mul r0, r4
mul r0, r4
mul r0, r4
mul r1, r4
mul r1, r4
mul r2, r4
add r0, r1
add r0, r2
add r0, r3

mov r10, r0
mov r0, r6
mov r1, r7
mov r2, r8
mov r3, r9
add r4, #1
cmp r10, #0
bne loop

sub r4, #1
mov r0, r4
pop {r4-r10}
bx lr

