# lab03-alhanson7210
lab03-alhanson7210 created by GitHub Classroom

# Due Tue Sept. 8th at 11:59 PM in your lab repo
# Background
1. This week in lecture we will develop the foundation for a parser for our little language called ntcalc

2. This lab asks you to expand on the given parser, adding code and data structures to fully implement the scanning and parsing of the language specified in the EBNF

3. It is still a future topic to interpret the parse tree and do something useful with it. This lab covers only parser output

4. Parsing refers to the process of identifying acceptable structures as defined by a language. For example, our scanner from Lab02 can accept the following:

```1 + 2```

This results in the following sequence of tokens:
```
TK_INTLIT("1")
TK_OP("+")
TK_INTLIT("2")
TK_EOT("")
```
We now need to "parse" these tokens to see if they represent a valid **ntcalc** program. Parsing will do two things for us. It will determine if a sequence of tokens is a valid program and it will construct a data structure from the tokens that can later be used for interpretation or compilation.

In language parsing we usually form a tree version of the program structure. For example, the token sequence above can be represented as the following tree:


We call this a parse tree (or technically an abstract syntax tree). The nodes in the tree represent different parts of the structure of a valid program. In this case, the program consists of a single expression. This expression is an operator with two arguments (or operands). The expression operator is a PLUS ("+") and the two operands are both INTVALS. 

We can represent this tree structure as a string:
```
EXPR OPER2 PLUS
..EXPR INTVAL 1
..EXPR INTVAL 2
```
Now consider the following ntcalc program:

```(1 + 2) * 3```

Here are the tokens:
```
TK_LPAREN("(")
TK_INTLIT("1")
TK_PLUS("+")
TK_INTLIT("2")
TK_RPAREN(")")
TK_MULT("*")
TK_INTLIT("3")
TK_EOT("")
```
Now here is the resulting parse tree for this token sequence:
```
|------|
|EXPR  |
|OPER2 |
|MULT  |
|------|
|       \
|        \
|         \
|------|   |------|
|EXPR  |   |EXPR  |
|OPER2 |   |INTVAL|
|PLUS  |   |3     |
|------|   |------|
|       \
|        \
|         \
|------|   |------|
|EXPR  |   |EXPR  |
|INTVAL|   |INTVAL|
|1     |   |2     |
|------|   |------|
```
Here is the string representation of this parse tree:
```
EXPR OPER2 MULT
..EXPR OPER2 PLUS
....EXPR INTVAL 1
....EXPR INTVAL 2
..EXPR INTVAL 3
```
Our goal in parsing is to construct the tree structure of valid ntcalc programs. Notice how in both the tree and the string output the parens are no longer present. This is because the tree form implicitly represents the grouping that is specified in the parens. So, we discard the parens themselves, but not what they represent in terms of program structure.

For this lab, we are going to simplify the ntcalc language so we can focus on the basics of parsing.

Here is the EBNF for the scanner of our simplified ntcalc language:
```
tokenlist   ::= (token)*
token       ::= integer | symbol
integer     ::= digit (digit)*
symbol      ::= '+' | '-' | '*' | '/' | '(' | ')'
digit       ::= '0' | ... | '9'

# Ignore
whitespace  ::=  (' ' | '\t') (' ' | '\t')*
```
We can also represent the structure of valid ntcalc programs with EBNF:
```
expression  ::= operand (operator operand)* EOT
operand     ::= integer
              | '-' operand
              | '(' expression ')'
```
We are going to limit valid ntcalc programs to expessions. For example, the following are valid expressions:
```
1 + 2
(1 + 2) * 3
4 * (10 / 5)
(2 * (3 + (1 + 1)))
-4 + 3
-4 + -4
```
Just like with scanning, the EBNF specifies valid programs in terms of tokens. An expression can be an operand follow by and operator and another operand. An operand can be a integer, or a '-' then an operand, or another expression with in parens.

We also need a data structure in C that will represent the tree structures given above. Here is the struct we will use:
```
enum parse_expr_enum {EX_INTVAL, EX_OPER1, EX_OPER2};
enum parse_oper_enum {OP_PLUS, OP_MINUS, OP_MULT, OP_DIV};

struct parse_node_st {
    enum parse_expr_enum type;
    union {
        struct {int value;} intval;
        struct {enum parse_oper_enum oper;
                struct parse_node_st *expr;} oper1;
        struct {enum parse_oper_enum oper;
                struct parse_node_st *left;
                struct parse_node_st *right;} oper2;
    };
 };
```
We are going to derive a parser implementation from the EBNF for expressions given above to construct a tree of parse_node_st struct. The type of parser we are going to implement is a *recursive descent parser*. The basic idea is to write a function for each production in the grammar. So, our simplified version of ntcalc, we will have two parse functions:
```
struct parse_node_st * parse_operand(struct parse_table_st *pt,
                                      struct scan_table_st *st);
struct parse_node_st * parse_expression(struct parse_table_st *pt,
                                       struct scan_table_st *st);
```
Given a sequence of token in a ```scan_table_st```, we will recursively construct a parse tree by allocating ```parse_node_st``` structs from the parse_table.

# Requirements
Your job is to implement a parser, called **lab03**, that will work like this:
```
./lab03 -e "1 + 2"
EXPR OPER2 PLUS
..EXPR INTVAL 1
..EXPR INTVAL 2
```
That is, the parser will take an input expression on the command line after the "-e" option. It will scan the input expression string, then parse it into a parse_node tree. Finally, it will walk the tree to generate the output shown above.

Here is the correct output for the other example expressions above:
```
./lab03 -e "(1 + 2) * 3"
EXPR OPER2 MULT
..EXPR OPER2 PLUS
....EXPR INTVAL 1
....EXPR INTVAL 2
..EXPR INTVAL 3
```
```
./lab03 -e "4 * (10 / 5)"
EXPR OPER2 MULT
..EXPR INTVAL 4
..EXPR OPER2 DIV
....EXPR INTVAL 10
....EXPR INTVAL 5
```
```
./lab03 -e "(2 * (3 + (1 + 1)))"
EXPR OPER2 MULT
..EXPR INTVAL 2
..EXPR OPER2 PLUS
....EXPR INTVAL 3
....EXPR OPER2 PLUS
......EXPR INTVAL 1
......EXPR INTVAL 1
```
```
./lab03 -e "-4 + 3"
EXPR OPER2 PLUS
..EXPR OPER1 MINUS
....EXPR INTVAL 4
..EXPR INTVAL 3
```
```
./lab03 -e "-4 + -4"
EXPR OPER2 PLUS
..EXPR OPER1 MINUS
....EXPR INTVAL 4
..EXPR OPER1 MINUS
....EXPR INTVAL 4
```
# Deliverables
1. Please start with the starter repo in the GitHub Classroom assignment for your section. The assignment URL will be given in Piazza.

2. Your repo must contain a ```Makefile``` which builds an executable called ```lab03``` using the source files ```scan.c``` and ```parse.c```

3. Use the techniques we learned for reading files and analyzing text to build up a tree of ```parse_node_st``` structs.

4. Print out the parse nodes **exactly** as shown above to get credit for correctness
