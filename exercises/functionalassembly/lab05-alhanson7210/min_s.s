/* min_s.s - simple min function */

.global min_s

/* a is r0, b is r1 */
end:	
    bx lr

ar0:
	b end
	
br1:
	mov r0, r1
	b end

min_s:
    /*mov r0, #0 DELETE this line and add correct instructions. */
    cmp r0, r1
    bge br1
    b ar0
