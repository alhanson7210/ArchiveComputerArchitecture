.global search_s

@ * binary search: searchs_s - repeatedly identify the middle index approach x in the array or a search error
@ * r0 -> arr
@ * r1 -> left
@ * r2 -> right
@ * r3 -> x
@ * r4 -> mid
@ * r5 -> arr[mid]

search_s:
    sub sp, sp, #4
    str lr, [sp] 
    cmp r2, r1 
    blt search_error 
    sub r4, r2, r1 
    lsr r4, r4, #1 
    add r4, r1, r4 
    lsl r6, r4, #2
    ldr r5, [r0, r6] 
    cmp r5, r3 
    beq search_condition_eq 
    bgt search_condition_gt 
    b search_condition_lt 

search_condition_eq:
    mov r0, r4
    b search_end  
search_condition_gt:
    sub r4, r4, #1 
    mov r2, r4 
    b recursive_call  
search_condition_lt:
    add r4, r4, #1  
    mov r1, r4 
recursive_call:
    bl search_s 
    b search_end 

search_error:
    mov r0, #-1 
search_end:
    ldr lr, [sp] 
    add sp, sp, #4 
    bx lr 

