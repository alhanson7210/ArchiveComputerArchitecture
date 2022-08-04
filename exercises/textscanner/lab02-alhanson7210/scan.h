//begin macro
#ifndef _SCAN_H
#define _SCAN_H
//needed system libraries
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//global
#define SCAN_TOKEN_LEN 32
#define SCAN_TOKEN_TABLE_LEN 1024
#define FILE_TABLE_LEN 8192
#define SCAN_STRINGS {"INTLIT", "STRLIT", "LPAREN", "RPAREN", \
                      "PLUS", "MINUS", "MULT", "DIV", "EQ", \
                      "IDENT", "EOL", "EOT"};
//enumerations
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
//structures
struct scan_token_st {
    enum scan_token_enum id;
    char name[SCAN_TOKEN_LEN];
    int len;
};

struct scan_table_st {
    struct scan_token_st table[SCAN_TOKEN_TABLE_LEN];
    int len;
};

struct file_table_st {
    char text[FILE_TABLE_LEN];
    int len;
    char *end;
};
//prototypes
void scan_table_init(struct scan_table_st * tt);
void scan_file_table_init(struct file_table_st * ftbl);
int scan_file_table_read(struct file_table_st * ftbl, char * ntc_file);
void scan_table_add(struct scan_table_st * tt, enum scan_token_enum id, char * token);
bool is_eol(char ch);
bool is_whitespace(char ch);
bool is_digit(char ch);
bool is_symbol(char ch);
bool is_letter(char ch);
bool is_ident(char ch);
bool is_quote(char ch);
bool is_comment(char ch);
void scan_symbol(struct scan_table_st * tt, char ch);
char * skip_whitespace(char * input, char * end);
char * skip_comment(char * input, char * end);
char * scan_intlit(struct scan_table_st * tt, char * p, char * end);
char * scan_ident(struct scan_table_st * tt, char * p, char * end);
char * scan_strlit(struct scan_table_st * tt, char * p, char * end);
char * scan_ntokens(struct scan_table_st * tt, char * input, char * end);
void scan_table_scan(struct scan_table_st * tt, char * input, int len);
void scan_table_print(struct scan_table_st * tt);
//end macro
#endif
