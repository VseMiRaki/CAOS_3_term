    .intel_syntax noprefix
    .global summ
summ:
    push    ebp
    mov     ebp, esp
    push    ebx
    push    esi
    mov     ecx, [ebp + 8]
    .Loop:
        mov     ebx, ecx
        dec     ebx
        mov     eax, [ebp + 12]
        mov     eax, [eax + 4 * ebx]
        mov     esi, [ebp + 20]
        mov     [esi + 4 * ebx], eax
        mov     esi, [ebp + 16]
        mov     eax, [esi + 4 * ebx]
        mov     esi, [ebp + 20]
        add     [esi + 4 * ebx], eax   
        loop .Loop
    pop     esi
    pop     ebx
    mov     esp, ebp
    pop     ebp
    ret
