.global reverse_s

@ * reverse char array: revers_s - swap ends while appraoching the middle
@ * r0 is buf buf
@ * r1 is buf end
@ * r2 is btemp
@ * r3 is etemp
 
reverse_s:
    mov r1, r0 
find_end_loop:
    ldrb r3, [r1] 
    cmp r3, #0 
    bne find_end_continue
    b find_end_reached
find_end_continue:
    add r1, r1, #1 
    b find_end_loop
find_end_reached:
    sub r1, r1, #1 
reverse_loop:
    cmp r0, r1 
    blt reverse_body 
    b reverse_end 
reverse_body:
    ldrb r2, [r0] 
    ldrb r3, [r1] 
    strb r3, [r0] 
    strb r2, [r1] 
    add r0, r0, #1 
    sub r1, r1, #1 
    b reverse_loop 
reverse_end:
    bx lr 
