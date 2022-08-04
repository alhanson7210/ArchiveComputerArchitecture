# project06-alhanson7210
project06-alhanson7210 created by GitHub Classroom

# Due: 
* December 2 at 11:59 PM to the Github Classroom repo published in your section's Piazza

* Submit all of the .dig files and .hex files required to run your simulation

* Project06 will be graded in an Interactive Grading meeting. Please sign up using the spreadsheet published in your section's Piazza

## Requirements
- You will implement and simulate a simplified ARM microarchitecture in Digital

- You may use any of Digital's library of components

- We will introduce some new and useful tools and techniques for Digital in lecture

- Your processor must be able to execute the following programs:

* quadratic_s

* sum_array_s

* fact_s

* Your Project03 solution to search_s

* Your Project03 solution to sort_s

* In order to make your programs runnable on your processor you must do the following:

  * You will add an assembly language main to set up the parameters for your functions

  * You will add the end marker (add r0, r0, #0) to signifiy when the program should stop

  * Ensure that you do not have .global or .func directives in your programs

- Your processor implementation will include the following major sub-circuits:

* The Program Counter (PC) will be one 32-bit register

* Machine code instructions will be stored in a ROM component, just as we did in Project05. Like in Project05 your instruction memory will be able to select the program you want to execute.

* The Arithmetic Logic Unit (ALU) will perform data processing tasks such as add, sub, mul, and mov.

* The Sign Extension Unit will perform sign extension, much like you did when calculating branch offsets in Project04 Data Memory. We will use a RAM component to hold data on the simulated stack. We will not simulate any cache or dynamic memory.

* The Control Unit will decode machine code instructions. As with Project05, the Control Unit will be the most complex part. 

* The Data Path will connect data between the various sub-circuits

* The Control Path will connect the Control unit to various sub-circuits and multiplexers

## Given
* We will discuss the major sub-circuits in lecture and you will have hands-on time to develop and ask questions

* We have compiled an implementation guide for Project06, available in two parts in the Resources section of this web site.

## Rubric
For interactive grading you should be able to run each of the tests below with the inputs given.

(10 points) quadratic_s(2, 4, 8 16) = 48

(10 points) fact_s(5) = 120

(10 points) sum_array(0, 4, 8, 12, 16, 5) = 40

(20 points) search_s({0, 4, 8, 12, 16}, 0, 5, 12) = 3

(20 points) sort_s({16, 4, 32, 2, 8}, 5) = {32, 16, 8, 4, 2}

(10 points) Neatness

(10 points) Interactive grading question #1

(10 points) Interactive grading question #2

## Extra Credit
You must complete all of the Project06 spec above in order to earn extra credit points. 

You can have until Thursday, December 10th at 11:59 PM to finish extra credit work.

1 point options:

(a) mvn - demonstrate with  search_s({0, 4, 8, 12, 16}, 0, 5, 13) = -1

(b) rsb instruction support.

(c) and, orr, eor instruction support.

5 point options:

(a) Implement support for the register form of STR: str r0, [r1, r2]. Provide a suitable test program that demonstrates your implementation works.

(b) Implement support for LDR and STR with shift support, e.g., ldr r0, [r1, #2, LSL 2].

(c) Implement support for LDR and STR with post increment and write back support.

(d) Conditional Execution support for all instructions. You need to come up with a demonstration program that proves your new conditional execution logic works for all instruction classes such as data processing, mul, sdt, bl, and bx.

10 point options:

(b) Block Data Transfer instruction support (LDM and STM). See section 4.11 in the ARM Instruction Set Reference. You need to provide a suitable test program which demonstrates that your implementation works.

(c) Single Data Swap instruction support (SWP). See section 4.12 in the ARM Instruction Set Reference. You need to provide a suitable test program which demonstrates that your implementation works.

(d) Implement a real-time disassembler for you top-level processor circuit so that you can see the instruction that is executing in a Digital Terminal component with the instruction name and the register names. 

Propose your own extra credit. Send a proposal to your instructor for consideration. We can determine if your proposal is worth extra credit and, if, so, the point value.

