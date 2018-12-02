#include <asm/unistd_32.h>

.intel_syntax noprefix
.text
.global _start
_start:
   
loop:
    //read

    mov     eax, __NR_read
    mov     ebx, 0
    mov     ecx, string_ptr
    mov     edx, 1
    int     0x80
    
    cmp     eax, 0
    jle     end

    //print
    mov     eax, __NR_write 
    mov     ebx, 1
    mov     ecx, string_ptr
    mov     edx, 1
    int     0x80
    jmp     loop
    
end:
    mov     eax, __NR_exit
    mov     ebx, 0
    int     0x80

    .data
string:
    .string "\n"
string_ptr:
    .long string
