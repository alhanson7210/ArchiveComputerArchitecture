// resources
#include "scan.h"
//globals
#define ERROR -1
#define SUCCESS 0
#define NTC_FILE 1
#define FILE_READ 1
#define EXPECTED 2
#define CHARSZ sizeof(char)
#define EPSILON ""
//usgae & driver
void usage(int argc, char ** argv)
{
	int arg;
	printf("Given: ");
	for(arg = 0; arg < argc; arg++)
		printf("%s ", argv[arg]);
	printf("\nExpected ./lab02 NTC_FILE\n");
	exit(ERROR);
}

int
main(int argc, char ** argv)
{
	if (argc < EXPECTED)
		usage(argc, argv);
	//scan table init
	struct scan_table_st scan_tbl;
	scan_table_init(&scan_tbl);
	//scan table file
	struct file_table_st file_tbl;
	scan_file_table_init(&file_tbl);
	if (scan_file_table_read(&file_tbl, argv[NTC_FILE]) < 0)
		usage(argc, argv);
	//scan table scanner // text[file_tbl.len] is '\0'
	scan_table_scan(&scan_tbl, file_tbl.text, file_tbl.len);
	//scan table print
	scan_table_print(&scan_tbl);
	//end procedure
	return SUCCESS;
}
//implementation
void
scan_table_init(struct scan_table_st * tt)
{
	if (tt)
	{
		memset(tt, 0, sizeof(struct scan_table_st));
		tt->len = 0;
	}
}

void scan_file_table_init(struct file_table_st * ftbl)
{
	if(ftbl)
	{
		memset(ftbl, 0, sizeof(struct file_table_st));
		ftbl->len = 0;
		ftbl->end = 0;
	}
}

int 
scan_file_table_read(struct file_table_st * ftbl, char * ntc_file)
{
	//sanity check: NULL input
	if (!ftbl || !ntc_file)
		return ERROR;
	//sanity check: invalid file input
	FILE * n_f;
	if (!(n_f = fopen(ntc_file, "r")))
		return ERROR;
	//read entire file and close file on failure
	int n;
	if (!(n = fread(&ftbl->text, sizeof(char), FILE_TABLE_LEN, n_f)))
	{
		fclose(n_f);
		return ERROR;
	}
	//assign remaining fields
	ftbl->len = n;
	ftbl->end = &ftbl->text[n];
	fclose(n_f);
	//file read successfully
	return FILE_READ;
}

void
scan_table_add(struct scan_table_st * tt, enum scan_token_enum id, char * token)
{
	if (tt && tt->len != SCAN_TOKEN_TABLE_LEN)
	{
		tt->table[tt->len].id = id;
		strncpy(tt->table[tt->len].name, token, SCAN_TOKEN_LEN);
		++tt->len;
	}
}

bool
is_eol(char ch)
{
	return ch == '\n';
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
is_symbol(char ch)
{
	return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' || ch == '(' || ch == ')';
}

bool
is_letter(char ch)
{
	return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z');
}

bool
is_ident(char ch)
{
	return ch == '_' || is_letter(ch) || is_digit(ch);
}

bool
is_quote(char ch)
{
	return ch == '\"';
}

bool
is_comment(char ch)
{
	return ch == '#';
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
		case '=':
			scan_table_add(tt, TK_EQ, "=");
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

char*
skip_whitespace(char * input, char * end)
{
	while (input != end && is_whitespace(*input))
		input++;
	return input;
}

char*
skip_comment(char * input, char * end)
{
	while (input != end && !is_eol(*input))
		input++;
	//skip newline for comments
	if(is_eol(*input))
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
scan_ident(struct scan_table_st * tt, char * p, char * end)
{
	char str[SCAN_TOKEN_LEN] = { 0 };
	char *ps = str;
	while (p != end && is_ident(*p))
		*ps++ = *p++;
	scan_table_add(tt, TK_IDENT, str);
	return p;	
}

char*
scan_strlit(struct scan_table_st * tt, char * p, char * end)
{
	char str[SCAN_TOKEN_LEN] = { 0 };
	char *ps = str;
	//initial quote
	++p;
	while (p != end && !is_quote(*p))
		*ps++ = *p++;
	scan_table_add(tt, TK_STRLIT, str);
	//skip the last quote
	if (is_quote(*p))
		++p;
	return p;
}

char* 
scan_ntokens(struct scan_table_st * tt, char * input, char * end)
{
	//skip: whitespace char => primary skip
	if (is_whitespace(*input))
		input = skip_whitespace(input, end);
	//skip: comments => secondary skip
	if (is_comment(*input))
		input = skip_comment(input, end);
	//scanner check
	if (is_eol(*input))
	{
		scan_table_add(tt, TK_EOL, EPSILON);
		++input;
	}

	if (*input == *end)
	{
		scan_table_add(tt, TK_EOT, EPSILON);
	} else if (is_digit(*input))
	{
		input = scan_intlit(tt, input, end);
	} else if (is_symbol(*input))
	{
		scan_symbol(tt, *input);
		++input;
	} else if (is_letter(*input))
	{
		input = scan_ident(tt, input, end);
	} else if (is_quote(*input))
	{
		input = scan_strlit(tt, input, end);
	}
	//current char
	return input;
}

void
scan_table_scan(struct scan_table_st * tt, char * input, int len)
{
	char * tkn = input; //beginning char
	char * end = &input[len]; //last char --> '\0'
	do
	{
		tkn = scan_ntokens(tt, tkn, end);
	} while(tkn != end);
}

void 
scan_table_print(struct scan_table_st * tt)
{
	if (tt && tt->len > 0)
	{
		int tkn;
		char *tokens[] = SCAN_STRINGS;
		struct scan_token_st *token;
		for(tkn = 0; tkn < tt->len; tkn++)
		{
			token = &tt->table[tkn];
			printf("TK_%s(\"%s\")\n", tokens[token->id], token -> name);
		}
	}
}
