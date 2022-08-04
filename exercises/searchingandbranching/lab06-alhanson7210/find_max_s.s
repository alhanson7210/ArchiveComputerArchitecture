/* find_max_s - find the maximum value in an interger array */

.global find_max_s
    
find_max_s:
    ldr r2, [r0] /* set max */
    mov r3, #0 /* set counter */
    b find_max_loop /* start looping */
find_max_loop:
	ldr r12, [r0]
    cmp r3, r1 /* has the end been reached */
    beq find_max_end /* counter == n */
    cmp r12, r2 /* has a greater number been found */
    bgt find_max_update 
    b find_max_body
find_max_update:
    mov r2, r12 /* update max */
find_max_body:
    add r0, r0, #4 /* get next int */
    add r3, r3, #1 /* counter++ */
    b find_max_loop /* loop back again */
find_max_end:
    mov r0, r2 /* set return int */
    bx lr /* branch and exchange to next instruction */
