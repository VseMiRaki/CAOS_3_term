.data
    var1:
	    .word 1
	var2:
	    .word 1

    scan_format:
	    .asciz "%d %d"

	print_format:
	    .asciz "%d\n"


.text
.global main
    main:
        push   {lr}
	    ldr    r0, =scan_format
	    ldr    r1, =var1
	    ldr    r2, =var2
	    bl scanf
        
        ldr    r1, =var1
        ldr    r2, =var2
        ldr    r1, [r1]
        ldr    r2, [r2]
        add    r3, r1, r2

    	ldr    r0, =print_format	
        mov    r1, r3
    	bl     printf

        pop    {lr}
    	bx     lr
	

