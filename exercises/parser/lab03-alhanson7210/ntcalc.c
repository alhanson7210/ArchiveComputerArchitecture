#include "ntcalc.h"

#define EXPECTED 3
#define VALUE 2
#define FLAG 1
#define SUCCESS 0
#define ERROR -1
#define DEFAULT "-e"

int 
main(int argc, char **argv) {
    struct scan_table_st scan_table;
    struct parse_table_st parse_table;
    struct parse_node_st *parse_tree;
    char input[SCAN_INPUT_LEN] = { 0 };
    int len;

    if ((argc != EXPECTED) || (strncmp(argv[FLAG], DEFAULT, SCAN_TOKEN_LEN) != SUCCESS)) {
        printf("usage: ntcalc -e \"expr\"\n");
        printf("  example: ntcalc -e \"1 + 2\"\n");
        exit(ERROR);
    }

    strncpy(input, argv[VALUE], SCAN_INPUT_LEN);
    len = strnlen(input, SCAN_INPUT_LEN);

    scan_table_init(&scan_table);
    scan_table_scan(&scan_table, input, len);

    parse_table_init(&parse_table);
    parse_tree = parse_program(&parse_table, &scan_table);
    parse_tree_print(parse_tree);

    return SUCCESS;
}
