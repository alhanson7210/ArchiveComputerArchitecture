#ifndef _NTCALC_H
#define _NTCALC_H

#include <fcntl.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#define PARSE_TABLE_LEN 1024
#define SCAN_INPUT_LEN 2048
#define SCAN_TOKEN_LEN 32
#define SCAN_TOKEN_TABLE_LEN 1024
#define PARSE_STRINGS {"PLUS", "MINUS", "MULT", "DIV"};
#define SCAN_TOKEN_STRINGS {"TK_INTLIT", "TK_LPAREN", "TK_RPAREN", \
                            "TK_PLUS", "TK_MINUS", "TK_MULT", "TK_DIV", \
                            "TK_EOT", "TK_ANY"};

enum scan_token_enum {
    TK_INTLIT, /* -123, 415 */
    TK_LPAREN, /* ( */
    TK_RPAREN, /* ) */
    TK_PLUS,   /* + */
    TK_MINUS,  /* - */
    TK_MULT,   /* * */
    TK_DIV,    /* / */
    TK_EOT,    /* end of text */
    TK_ANY,    /* wildcard for parser */
};

enum parse_expr_enum {EX_INTVAL, EX_OPER1, EX_OPER2};
enum parse_oper_enum {OP_PLUS, OP_MINUS, OP_MULT, OP_DIV};

struct scan_token_st {
    enum scan_token_enum id;
    char value[SCAN_TOKEN_LEN];
};

struct scan_table_st {
    struct scan_token_st table[SCAN_TOKEN_TABLE_LEN];
    int len;
    int next;
};

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

struct parse_table_st {
    struct parse_node_st table[PARSE_TABLE_LEN];
    int len;
    int next;
};

void scan_table_init(struct scan_table_st * tt);
void scan_table_add(struct scan_table_st * tt, enum scan_token_enum id, char * token);
bool is_whitespace(char ch);
bool is_digit(char ch);
bool is_symbol(char ch);
void scan_symbol(struct scan_table_st * tt, char ch);
char * skip_whitespace(char * input, char * end);
char * scan_intlit(struct scan_table_st * tt, char * p, char * end);
char * scan_ntokens(struct scan_table_st * tt, char * input, char * end);
void scan_table_scan(struct scan_table_st * tt, char * input, int len);
void scan_table_print(struct scan_table_st * tt);
struct scan_token_st * scan_table_get(struct scan_table_st *st, int i);
bool scan_table_accept(struct scan_table_st *st, enum scan_token_enum tk_expected);

void parse_table_init(struct parse_table_st * pt);
struct parse_node_st * parse_node_new(struct parse_table_st * pt);
struct parse_node_st * parse_operand(struct parse_table_st * pt, struct scan_table_st * st);
struct parse_node_st * parse_expression(struct parse_table_st * pt, struct scan_table_st * st);
struct parse_node_st * parse_program(struct parse_table_st *pt, struct scan_table_st *st);
void parse_tree_print_indent(int level);
void parse_tree_print_expr(struct parse_node_st * np, int level);
void parse_tree_print(struct parse_node_st * np);

#endif
