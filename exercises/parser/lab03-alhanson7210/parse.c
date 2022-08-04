#include "ntcalc.h"
//DEFAULTS
#define ERROR -1
//USAGE ERROR
void
parse_error(char *err) 
{
    printf("parse_error: %s\n", err);
    exit(ERROR);
}
//GLOBALS
char *parse_oper_strings[] = PARSE_STRINGS;
//IMPLEMENTATTION
void 
parse_table_init(struct parse_table_st *pt) {
	memset(pt, 0, sizeof(struct parse_table_st));
   	pt->len = 0;
  	pt->next = 0;
}

struct parse_node_st * 
parse_node_new(struct parse_table_st *pt) {
	return &pt->table[pt->len++];
}

struct parse_node_st * 
parse_operand(struct parse_table_st *pt, struct scan_table_st *st) {
    struct scan_token_st *tp;
    struct parse_node_st *np;

    if (scan_table_accept(st, TK_INTLIT)) { //positive int
        tp = scan_table_get(st, -1);
        np = parse_node_new(pt);
        np->type = EX_INTVAL;
        np->intval.value = atoi(tp->value);
    } else if (scan_table_accept(st, TK_MINUS)) { //negative integer/expression
    	np = parse_node_new(pt);
    	np->type = EX_OPER1;
    	np->oper1.oper = OP_MINUS;
        np->oper1.expr = parse_operand(pt, st);
    } else if (scan_table_accept(st, TK_LPAREN)) { //expression
    	np = parse_expression(pt, st);
    	if (!scan_table_accept(st, TK_RPAREN))
    	    parse_error("Bad operand: TK_LPAREN expected TK_RPAREN after expression");
    } else { //unrecognised tokens
    	printf("token: %s", scan_table_get(st, 0)->value);
    	parse_error("Bad operand: unrecognized token");
    }
    return np;
}

struct parse_node_st * 
parse_expression(struct parse_table_st *pt, struct scan_table_st *st) {
    struct scan_token_st *tp;
    struct parse_node_st *np1, *np2;

    np1 = parse_operand(pt, st);
    tp = scan_table_get(st, 0);

	while(true)
	{
	    if (tp->id == TK_PLUS) { //plus operation
	        scan_table_accept(st, TK_ANY);
	        np2 = parse_node_new(pt);
	        np2->type = EX_OPER2;
	        np2->oper2.oper = OP_PLUS;
	        np2->oper2.left = np1;
	        np2->oper2.right = parse_operand(pt, st);
	        np1 = np2;
	    } else if (tp->id == TK_MINUS) { //minus operation
	    	scan_table_accept(st, TK_ANY);
	        np2 = parse_node_new(pt);
	        np2->type = EX_OPER2;
	        np2->oper2.oper = OP_MINUS;
	        np2->oper2.left = np1;
	        np2->oper2.right = parse_operand(pt, st);
	        np1 = np2;
	    } else if (tp->id == TK_MULT) { //multiplication operation
			scan_table_accept(st, TK_ANY);
	        np2 = parse_node_new(pt);
	        np2->type = EX_OPER2;
	        np2->oper2.oper = OP_MULT;
	        np2->oper2.left = np1;
	        np2->oper2.right = parse_operand(pt, st);
	        np1 = np2;
	    } else if (tp->id == TK_DIV) { //division operation
			scan_table_accept(st, TK_ANY);
	        np2 = parse_node_new(pt);
	        np2->type = EX_OPER2;
	        np2->oper2.oper = OP_DIV;
	        np2->oper2.left = np1;
	        np2->oper2.right = parse_operand(pt, st);
	        np1 = np2;
	    }  { //mainly for EOT && RPAREN cancellation //technically can be INTVAL cancellation as well depending on operand method
	        break;
	    }
    }

    return np1;
}

struct parse_node_st * parse_program(struct parse_table_st *pt, struct scan_table_st *st) {
    struct parse_node_st *np1;
    np1 = parse_expression(pt, st);
    if (!scan_table_accept(st, TK_EOT)) parse_error("Expecting EOT");    
    return np1;                                       
}

void 
parse_tree_print_indent(int level) {
    level *= 2;
    for (int i = 0; i < level; i++)
        printf(".");
}

void parse_tree_print_expr(struct parse_node_st *np, int level) {
    parse_tree_print_indent(level);
    printf("EXPR ");

    if (np->type == EX_INTVAL) {
        printf("INTVAL %d\n", np->intval.value);
    } else if (np->type == EX_OPER1) {
    	printf("OPER1 %s\n", parse_oper_strings[np->oper1.oper]);
    	parse_tree_print_expr(np->oper1.expr, level+1);
    } else if (np->type == EX_OPER2) {
        printf("OPER2 %s\n", parse_oper_strings[np->oper2.oper]);
        parse_tree_print_expr(np->oper2.left, level+1);
        parse_tree_print_expr(np->oper2.right, level+1);
    }
}

void parse_tree_print(struct parse_node_st *np) {
    parse_tree_print_expr(np, 0);
}
