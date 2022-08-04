#include "ntcalc.h"

#define EXPECTED 3
#define VALUE 2
#define FLAG 1
#define SUCCESS 0
#define ERROR -1
#define DEFAULT "-e"
#define BINARY "-b"

int 
main(int argc, char **argv) {
    struct scan_table_st scan_table;
    struct parse_table_st parse_table;
    struct parse_node_st *parse_tree;
    char input[SCAN_INPUT_LEN] = { 0 };
    unsigned int result;
    int len, width, base, i, e;

    if (argc < EXPECTED)
    {
    	printf("usage: ntcalc -e \"expr\" -b base\n");
    	printf("  example: ntcalc -e \"1 + 2\" -b 2\n");
    	exit(ERROR);
    }
    result = 0;
    e = 0;
    base = 10;
    width = 32;

    for (i = 1; i < argc; i += 2)
    {
    	if (strncmp(argv[i], DEFAULT, SCAN_TOKEN_LEN) == SUCCESS)
    	{
    		e++;
    		strncpy(input, argv[VALUE], SCAN_INPUT_LEN);
    		len = strnlen(input, SCAN_INPUT_LEN);
    		continue;
    	}
    	else if (strncmp(argv[i], BINARY, SCAN_TOKEN_LEN) == SUCCESS)
    	{
    		base = parse_int(argv[i + 1], 10);
    		continue;
    	}
    	else
    	{
    		printf("usage: ntcalc -e \"expr\" -b base\n");
    		printf("  example: ntcalc -e \"1 + 2\" -b 2\n");
    		exit(ERROR);
    	}
    }
    
    if (!e/*(argc < EXPECTED) || (strncmp(argv[FLAG], DEFAULT, SCAN_TOKEN_LEN) != SUCCESS)*/) {
        printf("usage: ntcalc -e \"expr\" -b base\n");
        printf("  example: ntcalc -e \"1 + 2\" -b 2\n");
        exit(ERROR);
    }
    
    

    scan_table_init(&scan_table);
    scan_table_scan(&scan_table, input, len);
    // scan_table_print(&scan_table);

    parse_table_init(&parse_table);
    parse_tree = parse_program(&parse_table, &scan_table);
    // parse_tree_print(parse_tree);

	result = eval_tree(parse_tree);
	// printf("result %d\n", result);
	eval_print(result, width, base);
	
    return SUCCESS;
}
