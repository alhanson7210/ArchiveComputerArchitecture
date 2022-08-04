/* quadratic_s.s - quadratic function */

.global quadratic_s

/* x is r0, a is r1, b is r2, c is r3 */
quadratic_s:
    /* mov r0, #0 DELETE this line and add correct instructions. */
    mul r5, r1, r0 /*a times x*/
    mul r6, r5, r0 /*previous times x*/
    
    mul r7, r2, r0 /*b times x*/
    
    add r0, r6, r7 /*axx + bx*/
    add r0, r0, r3 /*previous + c*/

    bx lr
