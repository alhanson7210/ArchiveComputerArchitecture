/* add4_s.s - simple add function */

.global add4_s

/* a0 is r0, a1 is r1, a2 is r2, a3 is r3 */
add4_s:
    /* mov r0, #0 DELETE this line and add correct instructions. */
    add r4, r0, r1
    add r5, r2, r3
    add r0, r4, r5
    bx lr
