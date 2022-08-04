# lab02-alhanson7210
lab02-alhanson7210 created by GitHub Classroom

Due Monday, August 31st at 11:59pm in your lab GitHub repo.
Background
Over the next few weeks, we will build a scanner, parser, and interpreter for a little language we call ntcalc. The ntcalc language will be able to do the following types of calculations:
```
$ cat test.ntc
# Calculation
x = 2
y = 4
z = ((100 * 2) / 4) + 1
# Print result
printstr("z = ")
printdec(z)
println()
```
```
$ ./labo02 test.ntc
TK_IDENT("x")
TK_EQ("=")
TK_INTLIT("2")
TK_EOL("")
TK_IDENT("y")
TK_EQ("=")
TK_INTLIT("4")
TK_EOL("")
TK_IDENT("z")
TK_EQ("=")
TK_LPAREN("(")
TK_LPAREN("(")
TK_INTLIT("100")
TK_MULT("*")
TK_INTLIT("2")
TK_RPAREN(")")
TK_DIV("/")
TK_INTLIT("4")
TK_RPAREN(")")
TK_PLUS("+")
TK_INTLIT("1")
TK_EOL("")
TK_IDENT("printstr")
TK_LPAREN("(")
TK_STRLIT("z = ")
TK_RPAREN(")")
TK_EOL("")
TK_IDENT("printdec")
TK_LPAREN("(")
TK_IDENT("z")
TK_RPAREN(")")
TK_EOL("")
TK_IDENT("println")
TK_LPAREN("(")
TK_RPAREN(")")
TK_EOL("")
TK_EOT("")
```
Now if we run ntcalc on this file, we get:
```
$ ./ntcalc test.ntc
z = 51
```
Lab Requirements
In this lab you will use the concepts we discussed in lecture to build a text scanner (only) for ntcalc. We will address the parser and interpreter in subsequent lectures and assignments.

Here is a simple example for how your scanner should work:
```
$ cat simple.ntc
1 + 2
$ ./lab02 simple.ntc
TK_INTLIT("1")
TK_PLUS("+")
TK_INTLIT("2")
TK_EOL("")
TK_EOT("")
```

Here are two more examples:
```
$ cat vars.ntc
x = 2
y = x + 100
$ ./lab02 vars.ntc
TK_IDENT("x")
TK_EQ("=")
TK_INTLIT("2")
TK_EOL("")
TK_IDENT("y")
TK_EQ("=")
TK_IDENT("x")
TK_PLUS("+")
TK_INTLIT("100")
TK_EOL("")
TK_EOT("")
```

```
$ cat funcs.ntc
print("Hello, ntcalc!")
println()
$ ./lab02 funcs.ntc
TK_IDENT("print")
TK_LPAREN("(")
TK_STRLIT("Hello, ntcalc!")
TK_RPAREN(")")
TK_EOL("")
TK_IDENT("print")
TK_LPAREN("(")
TK_RPAREN(")")
TK_EOL("")
TK_EOT("")
```

```
We will define the set of acceptable tokens using EBNF (Extend Backus-Naur Form).

Here is the EBNF for ntcalc

tokenlist   ::= (token)*
token       ::= ident | integer | strlit | symbol | eol
ident       ::= letter ('_' | letter | digit)*
integer     ::= digit (digit)* 
symbol      ::= '+' | '-' | '*' | '/' | '=' | '(' | ')'
strlit       ::= '"' (char)* '"'
letter      ::= 'a' | ... | 'z' | 'A' | ... | 'Z'
digit       ::= '0' | ... | '9'
eol         ::= '\n'

# Ignore
whitespace  ::= ' ' | '\t' 
comment     ::= '#' (char)* eol
```


Here are some definitions you should use in your scan.c implementation:
```
#define SCAN_TOKEN_LEN 32
#define SCAN_TOKEN_TABLE_LEN 1024

enum scan_token_enum {
    TK_INTLIT, /* -123, 415 */
    TK_STRLIT, /* "hello" */
    TK_LPAREN, /* ( */
    TK_RPAREN, /* ) */
    TK_PLUS,   /* + */
    TK_MINUS,  /* - */
    TK_MULT,   /* * */
    TK_DIV,    /* / */
    TK_EQ,     /* = */
    TK_IDENT,  /* x, foo */
    TK_EOL,    /* end of line */
    TK_EOT,    /* end of text */
};

#define SCAN_STRINGS {"INTLIT", "STRLIT", "LPAREN", "RPAREN", \
                      "PLUS", "MINUS", "MULT", "DIV", "EQ", \
                      "IDENT", "EOL", "EOT"};

struct scan_token_st {
    enum scan_token_enum id;
    char name[SCAN_TOKEN_LEN];
    int len;
};

struct scan_table_st {
    struct scan_token_st table[SCAN_TOKEN_TABLE_LEN];
    int len;
};
```


The way to think about implementing a scanner given the EBNF is to create a function that will scan one token in the input string each time it is called. You need to figure out the starting character for each of the elements on the right-hand side of the token rule in the EBNF:
```
token       ::= ident | integer | symbol | strlit | eol
```
For the one-character elements such as symbol and eol, simply compare the next character in the input text to each of the possible one-character elements. If you find a match, then you create a corresponding token.

For multi-character elements such as ident, integer, and strlit, you will first see if the current character matches the beginning of one of these rules:

For identifier (ident), the first character must be a letter.

For an integer, the first character must be a digit.

For a string literal (strlit), the first character must be a double quote '"'.

Once you have determined if you are potentially looking at an ident, then you call a function to scan the rest of the ident and create an ident token. You will do the same process for integer and strlit.

Finally, your scanner should ignore both whitespace and comments, until the end of line.
```
# This is a comment
```
You implementation should have the following functions:
```
void scan_table_init(struct scan_table_st *tt);
void scan_table_scan(struct scan_table_st *tt, char *input, int len);
void scan_table_print(struct scan_table_st *tt);
```
You will need a way to read the contents of the input file into memory and pass a pointer to the file contents to scan_table_scan(). As a hint, you can use a fixed-size buffer and a structure like this:
```
#define FILE_TABLE_LEN 8192

struct file_table_st {
    char text[FILE_TABLE_LEN];
    int len;
    char *end;
};
```
Notes
For Windows users please make sure any test files you create are saved so that a single newline '\n' character to designate the end of line (not '\r\n').

Deliverables
Please start with the starter repo in the GitHub Classroom assignment for your section. The assignment URL will be given in Piazza.

Your repo must contain a Makefile which builds an executable called lab02 using the source file scan.c

Use the techniques we learned for reading files and analyzing text to build up the scan_table struct.

Print the token IDs and names out exactly as shown above to get credit for correctness
