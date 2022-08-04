/* fib_rec_s - recursive fibanocci */

.global fib_rec_s
.func fib_rec_s

fib_rec_s:
    sub sp, sp, #12 @ shrink stack
fib_rec_body:
    cmp r0, #0 @ base case x == 0
    beq fib_rec_zero
    cmp r0, #1
    beq fib_rec_one
    b fib_rec_recurse
fib_rec_zero:
    mov r1, #0
    b fib_rec_end
fib_rec_one:
    mov r1, #1
    b fib_rec_end
fib_rec_recurse:
    str lr, [sp] @ save lr
    str r0, [sp, #4] @ save old value of n in first var in sp    
    sub r0, r0, #1 @ r4 = n - 1
    bl fib_rec_s @ recursive call
    str r0, [sp, #8] @ save r2 as register to second var in sp
    ldr r0, [sp, #4] @ load old value of in from first var in sp
    sub r0, r0, #2 @ r4 = n - 2
    bl fib_rec_s @ recursive call 
    mov r1, r0 @ save r3 as register to third var in sp
fib_rec_add:
    ldr r0, [sp, #8]
    ldr lr, [sp] @ restore lr
    add r1, r0, r1 @ add both returned values and drop into end

fib_rec_end:
    mov r0, r1 @ obtain finished value
    add sp, sp, #12 @ grow stack
    bx lr
