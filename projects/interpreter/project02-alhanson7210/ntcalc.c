/* ntcalc.c */

#include "ntcalc.h"
#define DEFAULT 0
#define SUCCESS 0
#define DASH 0
#define WILDCARD 1
#define START 1
#define VALUE 1
#define CHARSIZE sizeof(char)
#define BASE 10
#define WIDTH 32

void ntlang_print_result(struct ntlang_config_st *nc, uint32_t result) {
  char result_str[SCAN_INPUT_LEN] = { 0 };

  conv_uint32_to_str(nc, result, result_str);
  printf("%s\n", result_str);
}

void ntlang_config_init(struct ntlang_config_st *cfg) {
  memset(cfg->input, DEFAULT , CHARSIZE * SCAN_INPUT_LEN);
  cfg->base = BASE;
  cfg->width = WIDTH;
  cfg->unsigned_output = false;
  cfg->verbose = false;
}

bool is_valid(char ch, int digit) {
  bool verify = false;
  switch(ch) {
    case 'b':
      switch (digit) {
        case 2:
          verify = true;
          break;
        case 10:
          verify = true;
          break;
        case 16:
          verify = true;
          break;
        default:
          break;
      }
      break;
    case 'w':
      switch(digit) {
        case 4:
          verify = true;
          break;
        case 8:
          verify = true;
          break;
        case 16:
          verify = true;
          break;
        case 32:
          verify = true;
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
  return verify;
}

int main(int argc, char **argv) {
  struct scan_table_st scan_table;
  struct parse_table_st parse_table;
  struct parse_node_st *parse_tree;
  struct ntlang_config_st cfg;
  uint32_t result;
  int len;

  result = DEFAULT;
  ntlang_config_init(&cfg);

  for (int a = START; a < argc; a++) {
    if (argv[a][DASH] == '-') {
      switch (argv[a][WILDCARD]) {
        case 'e':
          strncpy(cfg.input, argv[a+VALUE], SCAN_INPUT_LEN);
          len = strnlen(cfg.input, SCAN_INPUT_LEN);
          a++;
          break;
        case 'b':
          cfg.base = atoi(argv[a+VALUE]);
          if (!is_valid('b', cfg.base)) {
            cfg.base = BASE;
          }
          a++;
          break;
        case 'w':
          cfg.width = atoi(argv[a+VALUE]);
          if (!is_valid('w', cfg.width)) {
            cfg.width = WIDTH;
          }
          a++;
          break;
        case 'v':
          cfg.verbose = true;
          break;
        case 'u':
          cfg.unsigned_output = true;
          break;
      }
    }
  } 

  scan_table_init(&scan_table);
  scan_table_scan(&scan_table, cfg.input, len);
  if (cfg.verbose) {
    scan_table_print(&scan_table);
  }

  parse_table_init(&parse_table);
  parse_tree = parse_expression(&parse_table, &scan_table);
  if (cfg.verbose) {
    parse_tree_print(parse_tree);
  }

  result = eval_tree(parse_tree);
  ntlang_print_result(&cfg, result);

  return SUCCESS;
}
