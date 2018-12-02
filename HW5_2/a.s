    .intel_syntax noprefix
    .global mergesort
merge: /* (int *a, int left, int mid, int right) */
    push    ebp
    mov     ebp, esp

    mov     eax, [ebp + 20]
    sub     eax, [ebp + 12]
    lea     eax, [eax * 4]
    sub     esp, eax

    push    ebx
    push    esi
    push    edi
    
    /*
    right               ebp + 20
    mid                 ebp + 16
    left                ebp + 12 
    *a                  ebp + 8
    ret_adr
    old ebp <- ebp
    [right - left]      ebp - 4
    ebx                 
    esi
    edi <-esp       
                        ebp - 20 - right + left
    */

    mov ebx, 0
    mov esi, 0
    loop1:
/*if*/
        mov     eax, ebx
        add     eax, [ebp + 12]
        //add     eax, [ebp + 12], ebx
        cmp     eax, [ebp + 16]
        jge      endloop1
        mov     eax, esi
        add     eax, [ebp + 16]
        //add     eax, [ebp + 16], esi
        cmp     eax, [ebp + 20]
        jge      endloop1
//do
        mov     eax, ebx
        add     eax, [ebp + 12]
        mov     ecx, ebp
        add     ecx, 8
        mov     ecx, [ecx]
        mov     eax, [ecx + eax * 4]
        mov     edi, esi
        add     edi, [ebp + 16]
        mov     ecx, ebp
        add     ecx, 8
        mov     ecx, [ecx]
        mov     edi, [ecx + edi * 4]

// if a[left + it1] < a[mid + it2]
        cmp     eax, edi
        jl      if1
        jmp     else1

        if1:
            mov     eax, ebx
            add     eax, [ebp + 12]
            mov     ecx, ebp
            add     ecx, 8
            mov     ecx, [ecx]
            mov     edi, [ecx + eax * 4]
            mov     eax, ebx
            add     eax, esi
            mov     ecx, ebp
            sub     ecx, 4
            lea eax, [eax*4]
            sub     ecx, eax
            mov     [ecx], edi
            inc     ebx
            jmp    endif1

        else1:
            mov     eax, esi
            add     eax, [ebp + 16]
            mov     ecx, ebp
            add     ecx, 8
            mov     ecx, [ecx]
            mov     edi, [ecx + eax * 4]
            mov     eax, ebx
            add     eax, esi
            mov     ecx, ebp
            sub     ecx, 4
            lea eax, [eax*4]
            sub     ecx, eax
            mov     [ecx], edi
            inc     esi
            jmp    endif1

        endif1:
            jmp loop1
    
    endloop1:
    
    loop2:
        mov     eax, ebx
        add     eax, [ebp + 12]
        cmp     eax, [ebp + 16]
        jge      endloop2
//do
        mov     eax, ebx
        add     eax, [ebp + 12]
        mov     ecx, ebp
        add     ecx, 8
        mov     ecx, [ecx]
        mov     edi, [ecx + eax * 4]
        mov     eax, ebx
        add     eax, esi
        mov     ecx, ebp
        sub     ecx, 4
        lea eax, [eax*4]
        sub     ecx, eax
        mov     [ecx], edi
        inc     ebx
        jmp    loop2

    endloop2:
    
    loop3:
        mov     eax, esi
        add     eax, [ebp + 16]
        cmp     eax, [ebp + 20]
        jge      endloop3
//do   
        mov     eax, esi
        add     eax, [ebp + 16]
        mov     ecx, ebp
        add     ecx, 8
        mov     ecx, [ecx]
        mov     edi, [ecx + eax * 4]
        mov     eax, ebx
        add     eax, esi
        mov     ecx, ebp
        sub     ecx, 4
        lea     eax, [eax*4]
        sub     ecx, eax
        mov     [ecx], edi
        inc     esi
        jmp loop3
    endloop3:
    
    mov     edi, ebx
    add     edi, esi
    mov     ecx, 0
    loop4:
        cmp     ecx, edi
        jns     endloop4
//do
        mov     eax, ecx
        lea     eax, [eax * 4]
        mov     ebx, ebp
        sub     ebx, 4
        sub     ebx, eax 
        mov     ebx, [ebx]
        //все, кроме ebx
        mov     eax, ebp
        add     eax, 8
        mov     eax, [eax]
        mov     edx, ecx
        add     edx, [ebp + 12]
        lea     edx, [edx * 4]
        mov     [eax + edx], ebx

        
        inc     ecx
        jmp     loop4
   endloop4:

    pop     edi
    pop     esi
    pop     ebx
    mov     esp, ebp
    pop     ebp
    ret

mergesort:
    push    ebp
    mov     ebp, esp
    push    ebx
    push    esi
    push    edi
    /*
    out         ebp + 20
    in          ebp + 16
    to          ebp + 12
    from        ebp + 8
    ret_val     ebp + 4
    ebp         ebp
    ebx
    esi
    edi         esp
    
    */


    mov     edi, [ebp + 12]
    mov     ecx, 0
    loop:
        cmp     ecx, edi
        jge     endloop
//do
        mov     eax, ecx
        lea     eax, [eax * 4]
        mov     ebx, ebp
        add     ebx, 16
        mov     ebx, [ebx] 
        mov     ebx, [ebx + eax]
        //все, кроме ebx
        mov     eax, ebp
        add     eax, 20
        mov     eax, [eax]
        mov     edx, ecx
        lea     edx, [edx * 4]
        mov     [eax + edx], ebx

        inc     ecx
        jmp     loop
    endloop:
    

    mov     eax, [ebp + 12]
    sub     eax, [ebp + 8]
    push    [ebp + 12]
    push    [ebp + 8]
    push    [ebp + 20]
    call    mergeSortRecursive
    add     esp, 12

    pop     edi
    pop     esi
    pop     ebx
    mov     esp, ebp
    pop     ebp
    ret

mergeSortRecursive:
    push    ebp
    mov     ebp, esp
    push    ebx
    push    esi
    push    edi
    /*
    right       ebp + 16
    left        ebp + 12
    *a          ebp + 8
    ret_adr     ebp + 4
    ebp         ebp
    ebx
    esi
    edi*/
    
    mov     eax, [ebp + 12]
    inc     eax
    cmp     eax, [ebp + 16]
    jge     end
    
    mov     ebx, [ebp + 16]
    sub     ebx, [ebp + 12]
    shr     ebx, 1
    mov     eax, [ebp + 12]
    
    add     eax, ebx
    mov     esi, eax        
    push    esi
    push    [ebp + 12]
    push    [ebp + 8]
    call    mergeSortRecursive
    add     esp, 12

    push    [ebp + 16]
    push    esi
    push    [ebp + 8]
    call    mergeSortRecursive
    add     esp, 12
    
    push    [ebp + 16]
    push    esi
    push    [ebp + 12]
    push    [ebp + 8]
    call    merge
    add     esp, 16

    end:
        pop     edi
        pop     esi
        pop     ebx
        mov     esp, ebp
        pop     ebp
        ret


