# lab10-alhanson7210
lab10-alhanson7210 created by GitHub Classroom

Student: Alex Hanson 

Developer: @alhanson7210

Start: 11/19/2020

End: TBD

# [Lab10](https://cs315.cs.usfca.edu/labs/lab10) - Processor Simulation part 2

## Due Fri. 11/20 11:59 PM 

Please commit two directories to the Github Classroom repo published in your section's Piazza. Part1/ should contain the .dig files for your solution for Part 1 below. Part2/ should contain the .dig files for your solution to Part 2 below.

## Requirements
For this lab you will combine your work from [lab09](https://cs315.cs.usfca.edu/labs/lab9) with a new implementation of the Control circuits as described in the Project 06 Guide Part 2 

Use the spreadsheet approach to develop pseudo-Boolean algebra for the inputs (e.g. add(r), add(i) etc.) and outputs (e.g. ALUOp, ExtOp, etc.) for the circuit, as described in lecture.

We suggest you start by using 8 bits of input and 16 bits of output for the Data Processing instructions. You may need to add more as you add other instruction families.

## Part 1
Build the control unit and top-level processor circuit which can execute this program (also given in the Guide)
```
first_s:
    mov r0, #1
    mov r1, #2
    add r2, r0, r1
    add r0, r0, #0
```
## Part 2
Build the control and top-level processor circuit which can execute this program (also given in the Guide)
```
main:
    mov r0, #1
    mov r1, #2
    bl first_s
    add r0, r0, #0
first_s:
    add r0, r0, r1
    bx lr
```
Given
You may use any of the circuits shown in the [Project06 Guide Part 2](https://cs315.cs.usfca.edu/resources/project06-part-2).

You may use any of Digital's built-in components, or your own if you prefer.
