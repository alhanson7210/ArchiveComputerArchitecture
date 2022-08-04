.global sort_s

@ * linear search: find_max_s - find the maximum value in an interger array
@ * r0  -> array
@ * r1  -> len
@ * r2  -> i
@ * r3  -> max
@ * r4  -> index
@ * r5 -> array[i]

find_max_index_s:
    ldr r3, [r0] 
    mov r2, #0 
    mov r4, #0 
    b find_max_index_shift 
    
find_max_index_loop:
    cmp r2, r1 
    blt find_max_index_body 
    b find_max_index_end 

find_max_index_body:
    lsl r6, r2, #2
    ldr r5, [r0, r6] 
    cmp r5, r3 
    bgt find_max_index_update 
    b find_max_index_shift
    
find_max_index_update:
    mov r3, r5 
    mov r4, r2     
find_max_index_shift:
    add r2, r2, #1 
    b find_max_index_loop 
    
find_max_index_end:
    mov r0, r4 
    bx lr 
    
@ * max selection sort: sort_s - organizing integers from greatest to smallest
@ * r0 -> array
@ * r1 -> len
@ * r2 -> i
@ * r3 -> max_index
@ * r4 -> tmp = array[i]
@ * r5 -> array[max_index]
@ * r6 -> lr

sort_s:
    sub sp, sp, #16 
    str lr, [sp] 
    mov r2, #0 
sort_loop:
    cmp r2, r1 
    blt sort_body 
    b sort_end 

sort_body:
    str r0, [sp, #4] 
    str r1, [sp, #8] 
    str r2, [sp, #12] 
    lsl r4, r2, #2
    add r0, r0, r4 
    sub r1, r1, r2 
    
    bl find_max_index_s 
    mov r5, r3 
    mov r3, r0 
    ldr r2, [sp, #12] 
    ldr r1, [sp, #8] 
    ldr r0, [sp, #4] 
    add r3, r3, r2 
    cmp r3, r2
    bne sort_swap 
    b sort_continue  

sort_swap:
    lsl r6, r2, #2
    ldr r4, [r0, r6] 
    str r5, [r0, r6] 
    lsl r6, r3, #2
    str r4, [r0, r6] 
sort_continue:
    add r2, r2, #1
    b sort_loop 
    
sort_end:
    mov r0, r1 
    ldr lr, [sp] 
    add sp, sp, #16 
    bx lr 
