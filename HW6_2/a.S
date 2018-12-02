.intel_syntax noprefix
.text
.global dot_product
dot_product:
    push    ebp
    mov     ebp, esp
    push    ebx
    push    esi
    push    edi
    mov     edi, [ebp + 12]
    mov     esi, [ebp + 16]

    mov     eax, 0
    cvtsi2ss xmm2, eax

    mov     ecx, [ebp + 8]
loop:
    cmp     ecx, 0
    jz      end
    cmp     ecx, 1
    jz      modulo1
    cmp     ecx, 2
    jz      modulo2
    cmp     ecx, 3
    jz      modulo3
    
    mov     eax, ecx
    sub     eax, 4

    movups  xmm0, [esi + eax * 4]
    movups  xmm1, [edi + eax * 4]

    dpps    xmm0, xmm1, 0xFF
    addss   xmm2, xmm0
    sub     ecx, 4
    jmp     loop


modulo3:
    movups  xmm0, [esi]
    movups  xmm1, [edi]
    dpps    xmm0, xmm1, 0x77
    addss   xmm2, xmm0
    jmp     end

modulo2:
    movups  xmm0, [esi]
    movups  xmm1, [edi]
    dpps    xmm0, xmm1, 0x33
    addss   xmm2, xmm0
    jmp     end

modulo1:
    movups  xmm0, [esi]
    movups  xmm1, [edi]
    dpps    xmm0, xmm1, 0x11
    addss   xmm2, xmm0
    jmp     end

end:
    
    movss   [esp - 4], xmm2
    fld     dword ptr [esp - 4]
     
    pop     edi
    pop     esi
    pop     ebx
    mov     esp, ebp
    pop     ebp
    ret
     
     
     
     
     
     
     
    
     
     
     
