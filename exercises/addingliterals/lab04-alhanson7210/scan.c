#include "ntcalc.h"
//globals
#define ERROR -1
#define SUCCESS 0
#define NTC_FILE 1
#define FILE_READ 1
#define EXPECTED 2
#define CHARSZ sizeof(char)
#define EPSILON ""
//error
void scan_error(char *err) {
    printf("scan_error: %s\n", err);
    exit(ERROR);
}

//implementation
void
scan_table_init(struct scan_table_st * tt)
{
	memset(tt, 0, sizeof(struct scan_table_st));
	tt->len = 0;
	tt->next = 0;
}

void
scan_table_add(struct scan_table_st * tt, enum scan_token_enum id, char * token)
{
	tt->table[tt->len].id = id;
	strncpy(tt->table[tt->len++].value, token, SCAN_TOKEN_LEN);
}

bool
is_whitespace(char ch)
{
	return ch == ' ' || ch == '\t';
}

bool
is_digit(char ch)
{
	return '0' <= ch && ch <= '9';
}

bool
is_bit(char ch)
{
	return is_digit(ch) && (ch == '0' || ch == '1');
}

bool
is_bitlit(char * input)
{
	return (strncmp(input, "0b", 2) == 0)? true : false;
}

bool
is_symbol(char ch)
{
	return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' || ch == '(' || ch == ')';
}

bool
is_lshift(char ch)
{
	return ch == '<';
}

void
scan_symbol(struct scan_table_st * tt, char ch)
{
	switch(ch)
	{
		case '+':
			scan_table_add(tt, TK_PLUS, "+");
			break;
		case '-':
			scan_table_add(tt, TK_MINUS, "-");
			break;
		case '*':
			scan_table_add(tt, TK_MULT, "*");
			break;
		case '/':
			scan_table_add(tt, TK_DIV, "/");
			break;
		case '(':
			scan_table_add(tt, TK_LPAREN, "(");
			break;
		case ')':
			scan_table_add(tt, TK_RPAREN, ")");
			break;
		default:
			break;
	}
}

bool
is_bitsym(char ch)
{
	return ch == '~';
}

void
scan_bitsym(struct scan_table_st * tt, char ch)
{
	switch(ch)
	{
		case '~':
			scan_table_add(tt, TK_BWNOT, "~");
			break;
		default:
			break;
	}	
}

char*
skip_whitespace(char * input, char * end)
{
	while (is_whitespace(*input) && input != end)
		input++;
	return input;
}

char*
scan_intlit(struct scan_table_st * tt, char * p, char * end)
{
	char str[SCAN_TOKEN_LEN] = { 0 };
	char *ps = str;
	while (p != end && is_digit(*p))
		*ps++ = *p++;
	scan_table_add(tt, TK_INTLIT, str);
	return p;
}

char*
scan_bitlit(struct scan_table_st * tt, char * p, char * end)
{
	char str[SCAN_TOKEN_LEN] = { 0 };
	char *ps = str;
	p+=2; //skip 0b
	while (p != end && is_bit(*p))
		*ps++ = *p++;
	scan_table_add(tt, TK_BITLIT, str);
	return p;
}

char*
scan_lshift(struct scan_table_st * tt, char * p, char * end)
{
	char str[SCAN_TOKEN_LEN] = { 0 };
	char *ps = str;
	while (p != end && is_lshift(*p))
		*ps++ = *p++;
	scan_table_add(tt, TK_LSHIFT, str);
	return p;
}

char* 
scan_ntokens(struct scan_table_st * tt, char * input, char * end)
{
	//scanner check
	if (is_whitespace(*input))
	{
		input = skip_whitespace(input, end);
	}  
	else if (is_bitlit(input))
	{
		input = scan_bitlit(tt, input, end);
	}
	else if (is_digit(*input))
	{
		input = scan_intlit(tt, input, end);
	}
	else if (is_symbol(*input))
	{
		scan_symbol(tt, *input++);
	} 
	else if (is_bitsym(*input))
	{
		scan_bitsym(tt, *input++);
	}
	else if(is_lshift(*input))
	{
		input = scan_lshift(tt, input, end);
	}
	else 
	{
		printf("string: %s\n", input);
		scan_error("Invalid Token");
	}
	//needed this here in order to get the end of token since I guess it skips past it
	if (input == end)
	{
		scan_table_add(tt, TK_EOT, EPSILON);
	}
	//current char
	return input;
}

void
scan_table_scan(struct scan_table_st * tt, char * input, int len)
{
	char * tkn = input; //beginning char
	char * end = &input[len]; //last char --> '\0'
	while(true)
	{
		tkn = scan_ntokens(tt, tkn, end);
		if (tkn == end)
		{
			break;
		}
	}
}

void 
scan_table_print(struct scan_table_st * tt)
{
	if (tt && tt->len > 0)
	{
		int tkn;
		char *tokens[] = SCAN_TOKEN_STRINGS;
		struct scan_token_st *token;
		for(tkn = 0; tkn < tt->len; tkn++)
		{
			token = &tt->table[tkn];
			printf("%s(\"%s\")\n", tokens[token->id], token -> value);
		}
	}
}

struct scan_token_st * 
scan_table_get(struct scan_table_st *st, int i) {
    return &(st->table[st->next + i]);
}

bool 
scan_table_accept(struct scan_table_st *st, enum scan_token_enum tk_expected) {
    struct scan_token_st *tp;

    if (tk_expected == TK_ANY)
    {
    	st->next++;
    	return true;
    }
    
    tp = scan_table_get(st, 0);
    if (tp->id == tk_expected) {
        st->next++;
        return true;
    }

    return false;
}
