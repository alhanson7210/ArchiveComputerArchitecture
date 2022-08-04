.global sort_s2

/**
 * linear search: find_max_s - find the maximum value in an interger array
 * r0  -> array
 * r1  -> len
 * r2  -> i
 * r3  -> max
 * r4  -> index
 * r5 -> array[i]
 **/
find_max_index_s2:
    ldr r3, [r0] /* set max array[0] */
    mov r2, #0 /* set i to 0 */
    mov r4, #0 /* set max_index to 0 by default */
    b find_max_index_shift /* start i at 1 */
    
find_max_index_loop:
    cmp r2, r1 /*  i < len? */
    blt find_max_index_body /* look for max index */
    b find_max_index_end /* the end has been reached, goto next instruction */

find_max_index_body:
    ldr r5, [r0, r2, lsl # 2] /* current int value at array[i] */
    cmp r5, r3 /* array[i] > max? */
    bgt find_max_index_update /* yes */
    b find_max_index_shift /* no */
    
find_max_index_update:
    mov r3, r5 /* update max */
    mov r4, r2 /* update max index */    
find_max_index_shift:
    add r2, r2, #1 /* i++ */
    b find_max_index_loop /* loop back again */
    
find_max_index_end:
    mov r0, r4 /* set return max index */
    bx lr /* branch and exchange to next instruction */
    
/**
 * max selection sort: sort_s - organizing integers from greatest to smallest
 * r0 -> array
 * r1 -> len
 * r2 -> i
 * r3 -> max_index
 * r4 -> tmp = array[i]
 * r5 -> array[max_index]
 * r6 -> lr
 **/
sort_s2:
    sub sp, sp, #16 /* absorb stack space */
    str lr, [sp, #12] /* store lr into stack space */
    mov r2, #0 /* i = 0 */
sort_loop:
    cmp r2, r1 /* continue as long as i < len for i to len */
    blt sort_body /* continue sorting */
    b sort_end /* the end has been reached, goto next instruction */

sort_body:
    /* sort_body_prologue: */
    stm sp, {r0, r1, r2} 
    /* sort_call_prologue: */
    add r0, r0, r2, lsl #2 /* &array[i] */
    sub r1, r1, r2 /* len - i */
    /* sort_call: */
    bl find_max_index_s2 /* find the max index: find_max_index_s2(&array[i], len - i) */
    /* sort_call_epilogue: */
    mov r5, r3 /* r3 is max value from find_max_index_s or array[max_index] */
    mov r3, r0 /* initial value of max_index */
    /* sort_body_epiogue: */
    ldmia sp, {r0, r1, r2}
    /* sort_body_conditional: */
    add r3, r3, r2  /* max_index = initial value + i */
    cmp r3, r2 /* max_index != i? */
    bne sort_swap /* swap from position i with max_index */
    b sort_continue /* update and continue */   

sort_swap:
    ldr r4, [r0, r2, lsl #2] /* tmp = *(array + i) */
    str r5, [r0, r2, lsl #2] /* *(array + i) = *(array + max_index) */
    str r4, [r0, r3, lsl #2] /* *(array + max_index) = tmp */
sort_continue:
    add r2, r2, #1 /* i++ */
    b sort_loop /* continue sorting */
    
sort_end:
    mov r0, r1 /* return len */
    ldr lr, [sp, #12] /* restore lr */
    add sp, sp, #16 /* restore stack space */
    bx lr /* next instruction */
