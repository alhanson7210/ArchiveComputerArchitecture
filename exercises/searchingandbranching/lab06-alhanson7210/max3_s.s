/* max3_s.s - find the maximum value of three arguments using max2 */

.global max3_s

max2_s:
    cmp r0, r1
    bgt max2_end
    mov r0, r1
max2_end:
    bx lr

/* v0 - r0
 * v1 - r1
 * v2 - r2
 */
max3_s:
    sub sp, sp, #4 /* assumming I don't need 16 */
    str lr, [sp] /* store lr into stack space */
max3_body:
    bl max2_s /* cmp v0 and v1 (changes load register) */
    mov r1, r2 /* mov r2 into r1 to be cmp */
    bl max2_s /* cmp (v0|v1) and v2 */
max3_end:
    ldr lr, [sp] /* restore load register */
    add sp, sp, #4 /* assumming I don't need 16 */
    bx lr /* continue to whatever the next instruction is */
