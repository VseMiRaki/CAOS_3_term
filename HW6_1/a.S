.intel_syntax noprefix
.text
.global my_sin
my_sin:
    push    ebp
    mov     ebp, esp
    

    //xmm0 = x*x*(-1)
    movsd   xmm0, [ebp + 8]
    mulsd   xmm0, xmm0
    mov     eax, -1
    cvtsi2sd    xmm1, eax
    mulsd   xmm0, xmm1

    movsd   xmm1, [ebp + 8]
    movsd   xmm2, [ebp + 8]
    mov     ecx, 2
loop:
    mov     eax, 0
    mov     [esp - 4], eax
    cvtsi2sd   xmm4, [esp - 4]
    comisd  xmm2, xmm4
    jle     endloop

    mulsd   xmm2, xmm0
    
    cvtsi2sd xmm3, ecx
    divsd   xmm2, xmm3
    //ecx++
    
    inc     ecx
    cvtsi2sd xmm3, ecx
    divsd   xmm2, xmm3 
    inc     ecx

    addsd   xmm1, xmm2
    jmp     loop
    
endloop:
    
    movsd   [esp - 8], xmm1
    fld     qword ptr [esp - 8]

    mov     esp, ebp
    pop     ebp
    ret
