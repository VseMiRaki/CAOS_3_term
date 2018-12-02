#include <asm/unistd_32.h>

    .intel_syntax noprefix
    .text
    .global _start

_start:

    mov     eax, __NR_brk
    mov     ebx, 0
    int     0x80
    mov     [current_break], eax
    mov     [initial_break], eax
    mov     [new_break], eax
                            
            
expand:
    mov     eax, __NR_brk
    mov     ebx, [current_break]
    add     ebx, 1048576
    int     0x80
    mov     [new_break], eax
    jmp     continue

loop:
continue:
    
    mov     eax, [current_break]
    mov     ebx, [new_break]
    cmp     eax, ebx
    je      expand

    mov     eax, __NR_read
    mov     ebx, 0
    mov     ecx, current_break
    mov     edx, 512
    int     0x80
    add     [current_break], eax    

    cmp     eax, 512
    je      loop


    mov     eax, __NR_brk
    mov     ebx, [current_break]
    add     ebx, 1048576
    int     0x80
    mov     [new_break], eax
       
    mov     eax, [current_break]
    mov     ebx, [initial_break]
    cmp     eax, ebx
    je      end1
    
    
    mov     ebx, [current_break]
    mov byte ptr [ebx], 10

    mov     edi, [current_break]
    sub     edi, 1
loop2:

    mov     esi, 0
loop1:
    inc     esi
    cmp     edi, [initial_break]
    jle     end
    mov     cl, byte ptr [edi]
    
    cmp     cl, 10
    je      print
    dec     edi
    jmp     loop1

print:
    mov     eax, __NR_write
    mov     ebx, 1
    inc     edi
    mov     ecx, edi
    dec     edi
    dec     edi
    mov     edx, esi
    int     0x80
    jmp     loop2

end:
    mov     eax, __NR_write
    mov     ebx, 1
    mov     ecx, edi
    mov     edx, esi
    int     0x80
end1:
    mov     eax, __NR_brk
    mov     ebx, [initial_break]


    mov     eax, __NR_exit
    mov     ebx, 0
    int     0x80




.data
current_break:
    .long 0x0
new_break:
    .long 0x0
initial_break:
    .long 0x0

