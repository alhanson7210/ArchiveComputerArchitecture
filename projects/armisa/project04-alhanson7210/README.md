# project04-alhanson7210
project04-alhanson7210 created by GitHub Classroom
Due
10/26 at 11:59 PM to the Github assignment published in Piazza

Sign up for interactive grading using the schedule published in Piazza

Requirements 
You will write an assembler for a subset of the ARM Instruction Set Architecture (ISA), specified by the EBNF below

Your assembler must be called project04, and use the same command-line syntax as the GNU assembler
./project04 -o sort_s.o sort_s.s 

Your assembler must assemble your project03 solutions. You may simplify your project03 code if you wish, but no simpler than the EBNF below.

You will use the scanning and parsing techniques we learned for project02. 

You must not use translator generators like lex, yacc, bison, antlr, etc.

Once you have a parse tree, you will walk the parse tree and generate machine code instructions using the instruction formats we learned in lecture and labs.

Your assembler must support the command-line option -h to generate only a .hex file rather than a .o file
./project04 -h sort_s.hex sort_s.s

Given
In lecture and lab, we will illustrate extending the techniques we learned for project02 to this project using sample code.

You will be given a library which writes .o files in the ARM Executable and Linkable Format (ELF). Those .o files can be linked into an executable by gcc.

You will be given maketest test cases for known assembly-language source code. That way you can test your assembler's output before using it on your project03 solutions.

The EBNF for the ARM Assembly microsyntax (scanner):

    tokenlist   ::= (token)*
    token       ::= ident | imm | symbol
    ident       ::= letter (letter | digit | '_')*
    imm         ::= '#' ('-')+ digit (digit)*
    symbol      ::= '.' | '[' | ']' | ',' | ':'
    letter      ::= 'a' | ... | 'z' | 'A' | ... | 'Z'
    digit       ::= '0' | ... | '9'
    eol         ::= '\n'
# Ignore
    comment     ::= @ (char)* eol | '/' '*' (char | eol)* '*' '/'
    whitespace  ::=  (' ' | '\t') (' ' | '\t')*



The EBNF for the required subset of the ARM ISA is:

program     ::= statements EOT
statements  ::= statement 
              | statement EOL statements
statement   ::= directive
              | label ":" instruction
              | instruction

directive   ::= "." ident
label       ::= alpha (alpha | digit | "_")*
alpha       ::= "a" ... "z" | "A" ... "Z"
digit       ::= "0" ... "9"
instruction ::= cmp register "," register
              | cmp register "," immediate

              | dp register "," register "," register
              | dp register "," register "," immediate
              | ls register "," register "," register
              | ls register "," register "," immediate
              | mem register "," "[" register "]"
              | mem register "," "[" register "," immediate "]"
               | mul register, "," register, "," register
              | branch label
              | bx register
register    ::= "r0" | "r1" | ...| "r15" | "sp" | "lr" | "ip"
cmp         ::= "cmp"
dp          ::= "add" | "mov" | "sub"
ls          ::= "lsl" | "lsr"
mem         ::= "ldr" |"ldrb" | "str" | "strb"
mul         ::= "mul"
branch      ::= "b" | "bl" | "beq" | "bne" | "bgt" | "bge" | "blt" | "ble"
bx          ::= "bx"

Grading Rubric
Automated testing

20 pts: maketest tests with 10 trivial examples of various instructions (2 pts each)
20 pts: maketest tests with two known programs: quadratic_s.s and reverse_s.s (10 pts each)

Interactive grading

50 pts: Show your project04 solution assembling and running your project03 solutions for search_s.s and sort_s.s (25 pts each). To do this

In your project03 Makefile

AS=as
%.o: %.s
    $(AS) -o $@ $<

then change AS to

AS=../project04/project04

Then you can

$ make clean
$ make

and make will call your project04 assembler to build the source files

Breakdown of the 25 pts per program
15 pts: Successful demonstration
10 pts: Q&A about your design and implementation

Coding Style

10 pts: Clean repo, consistent naming and indentation, no dead code, no unnecessarily complex code
