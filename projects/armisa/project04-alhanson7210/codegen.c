/* codegen.c - machine code generation */

#include "armasm.h"

struct codegen_map_st codegen_opcode_map[] = CODEGEN_OPCODE_MAP;
struct codegen_map_st codegen_bcc_map[] = CODEGEN_BCC_MAP;

#define COND_BIT 28

void codegen_error(char *err) {
    printf("codegen_error: %s\n", err);
    exit(-1);
}

void codegen_table_init(struct codegen_table_st *ct, struct parse_node_st *tree) {
    ct->len = 0;
    ct->next = 0;
    ct->tree = tree;
    ct->label_count = 0;
    ct->public_count = 0;
}

void codegen_add_inst(struct codegen_table_st *ct, uint32_t inst) {
    ct->table[ct->len] = inst;
    ct->len += 1;
}

void codegen_table_add_pair(struct codegen_label_pair *lp, int index, 
    char *label, int offset) {
    strncpy(lp[index].label, label, SCAN_TOKEN_LEN);
    lp[index].offset = offset;
}

bool codegen_is_public_label(struct codegen_table_st *ct, struct codegen_label_pair *pl) {
    for (int l = 0; l < ct->public_count; l++) {
        if (!strcmp(ct->publics[l].label, pl->label))
            return true;
    }
    return false;
}

uint32_t codegen_lookup(char *name, struct codegen_map_st *map, int map_len) {
    int i;
    for (i = 0; i < map_len; i++) {
        if (strncmp(name, map[i].name, SCAN_TOKEN_LEN) == 0) {
            return map[i].bits;
        }
    }

    codegen_error(name);
    return (uint32_t) -1;
}

uint32_t codegen_lookup_opcode(char *name) {
    int len = sizeof(codegen_opcode_map) / sizeof(codegen_opcode_map[0]);
    return codegen_lookup(name, codegen_opcode_map, len);
}

uint32_t codegen_lookup_bcc(char *name) {
    int len = sizeof(codegen_bcc_map) / sizeof(codegen_bcc_map[0]);
    return codegen_lookup(name, codegen_bcc_map, len);
}

void codegen_generate_label_pairs(struct codegen_table_st *ct, struct parse_node_st *np, int level) {
    int offset = level << 2;
	if (np->type == INST) {
	    if (strlen(np->stmt.inst.label) > 0) {
	        codegen_table_add_pair(ct->labels, ct->label_count++, np->stmt.inst.label, offset);
	    }
	} else if (np->type == SEQ) {
	    if (np->stmt.seq.left->type == DIR) {
	    	codegen_table_add_pair(ct->publics, ct->public_count++, np->stmt.seq.left->stmt.dir.label, offset);
	    } else {
	    	codegen_generate_label_pairs(ct, np->stmt.seq.left, level++);
	    }
		codegen_generate_label_pairs(ct, np->stmt.seq.right, level);
	}
}

void codegen_dp_common(struct codegen_table_st *ct, uint32_t imm, uint32_t op, 
    uint32_t s, uint32_t rn, uint32_t rd, uint32_t op2) {
    const uint32_t DP_CONST_BIT = 26;
    const uint32_t DP_IMM_BIT = 25;
    const uint32_t DP_OP_BIT  = 21;
    const uint32_t DP_S_BIT  = 20;
    const uint32_t DP_RN_BIT  = 16;
    const uint32_t DP_RD_BIT  = 12;
    uint32_t inst = 0;

    inst = (COND_AL << COND_BIT)
        | (0b00 << DP_CONST_BIT)
        | (imm << DP_IMM_BIT)
        | (op  << DP_OP_BIT)
        | (s   << DP_S_BIT)
        | (rn  << DP_RN_BIT)
        | (rd  << DP_RD_BIT)
        | op2;
    codegen_add_inst(ct, inst);
}

void codegen_cmp(struct codegen_table_st *ct, struct parse_node_st *np) {
    codegen_dp_common(
        ct,
        0, /* rm is a reg */
        codegen_lookup_opcode(np->stmt.inst.name),
        1, /* alter codes */
        np->stmt.inst.cmp.rn,
        0, /* rd is unused */
        np->stmt.inst.cmp.rm);
}

void codegen_cmpi(struct codegen_table_st *ct, struct parse_node_st *np) {
    codegen_dp_common(
        ct,
        1, /* rm is a imm */
        codegen_lookup_opcode(np->stmt.inst.name),
        1, /* alter codes */
        np->stmt.inst.cmp.rn,
        0, /* rd is unused */
        np->stmt.inst.cmp.rm);
}

uint32_t codegen_mov_check_imm(struct parse_node_st *np) {
    uint32_t op = codegen_lookup_opcode(np->stmt.inst.name);
    if (op == 0b1101 && (int)np->stmt.inst.mov.rm < 0)
    {
        op = 0b1111;
        np->stmt.inst.mov.rm = ~np->stmt.inst.mov.rm;
    }
    return op;
}

void codegen_mov(struct codegen_table_st *ct, struct parse_node_st *np) {
    codegen_dp_common(
        ct,
        0, /* rm is a reg */
        codegen_lookup_opcode(np->stmt.inst.name),
        0, /* maintain codes */
        0, /* rn is unused */
        np->stmt.inst.mov.rd,
        np->stmt.inst.mov.rm);
}

void codegen_movi(struct codegen_table_st *ct, struct parse_node_st *np) {
    uint32_t op = codegen_mov_check_imm(np);
    codegen_dp_common(
        ct,
        1, /* rm is a imm */
        op,
        0, /* maintain codes */
        0, /* rn is unused */
        np->stmt.inst.mov.rd,
        np->stmt.inst.mov.rm);
}

void codegen_dp3(struct codegen_table_st *ct, struct parse_node_st *np) {
    codegen_dp_common(
        ct,
        0, /* rm is a register */
        codegen_lookup_opcode(np->stmt.inst.name),
        0, /* maintain codes */
        np->stmt.inst.dp3.rn,
        np->stmt.inst.dp3.rd,
        np->stmt.inst.dp3.rm);
}

void codegen_dp3i(struct codegen_table_st *ct, struct parse_node_st *np) {
    codegen_dp_common(
        ct,
        1, /*rm is an imm */
        codegen_lookup_opcode(np->stmt.inst.name),
        0, /* maintain codes */
        np->stmt.inst.dp3.rn,
        np->stmt.inst.dp3.rd,
        np->stmt.inst.dp3.rm);
}

uint32_t codegen_ls_shift_bits(char * name) {
    uint32_t ls;
    char c = *name;
    switch (c) {
        case 'l': ls = !(strcmp(name, "lsl"))? 0b00 : 0b01 ;break;
        case 'a': ls = 0b10; break;
        case 'r': ls = 0b11; break;
        default: ls = 0b00; break; //codegen error?
    }
    return ls;
}

void codegen_ls_alter_op2(struct parse_node_st *np, bool imm)
{
    const uint32_t LS_TYPE_BIT = 5;
    const uint32_t LS_START_CONST_BIT = 4;
    uint32_t CONST;
    uint32_t ls = codegen_ls_shift_bits(np->stmt.inst.name);
    if (imm) { //rs is a imm
        const uint32_t LS_AMOUNT_BIT = 7;
        CONST = 0b0;
        np->stmt.inst.ls.rm = (np->stmt.inst.ls.rs << LS_AMOUNT_BIT)
            | (ls << LS_TYPE_BIT)
            | (CONST << LS_START_CONST_BIT)
            | (np->stmt.inst.ls.rm);
    } else { //rs is a reg
        const uint32_t LS_REG_BIT = 8;
        const uint32_t LS_END_CONST_BIT = 7;
        np->stmt.inst.ls.rm = (np->stmt.inst.ls.rs << LS_REG_BIT)
            | (ls << LS_TYPE_BIT)
            | (0b0 << LS_END_CONST_BIT)
            | (0b1 << LS_START_CONST_BIT)
            | (np->stmt.inst.ls.rm);
    }
}

void codegen_ls(struct codegen_table_st *ct, struct parse_node_st *np) {
    codegen_ls_alter_op2(np, false);
    codegen_dp_common(
        ct,
        0, /* always a register  */
        codegen_lookup_opcode(np->stmt.inst.name),
        0, /* maintain codes */
        0, /* rn is unsed*/
        np->stmt.inst.ls.rd,
        np->stmt.inst.ls.rm);
}

void codegen_lsi(struct codegen_table_st *ct, struct parse_node_st *np) {
    codegen_ls_alter_op2(np, true);
    codegen_dp_common(
        ct,
        0, /* always a register  */
        codegen_lookup_opcode(np->stmt.inst.name),
        0, /* maintain codes */
        0, /* rn is unsed*/
        np->stmt.inst.ls.rd,
        np->stmt.inst.ls.rm);
}

void codegen_mem_common(struct codegen_table_st *ct, char *name, uint32_t imm, uint32_t rd,
    uint32_t rn, uint32_t updown, uint32_t offset) {
    const uint32_t MEM_CONST_BIT = 26;
    const uint32_t MEM_IMM_BIT = 25;
    const uint32_t MEM_PRE_BIT = 24;
    const uint32_t MEM_UPDOWN_BIT = 23;
    const uint32_t MEM_B_BIT = 22;
    const uint32_t MEM_W_BIT = 21;
    const uint32_t MEM_LDRSTR_BIT = 20;
    const uint32_t MEM_RN_BIT = 16;
    const uint32_t MEM_RD_BIT = 12;
    
    uint32_t ls;
    if ((strcmp(name, "ldr") == 0) | (strcmp(name, "ldrb") == 0)) { /* load : store */
        ls = 1;
    } else {
        ls = 0;
    }
    
    uint32_t b, w = 0b0;
    if ((strcmp(name, "ldrb") == 0) | (strcmp(name, "strb") == 0)) { /* byte : word */
        b = 0b1;
    }
    else {
        b = 0b0;
    }
    
    uint32_t inst = 0; /*  writeback = 0 */
    inst = (COND_AL << COND_BIT)
        | (0b01 << MEM_CONST_BIT)
        | (imm  << MEM_IMM_BIT)
        | (1 << MEM_PRE_BIT)
        | (updown << MEM_UPDOWN_BIT)
        | (b << MEM_B_BIT)
        | (w << MEM_W_BIT)
        | (ls << MEM_LDRSTR_BIT)
        | (rn << MEM_RN_BIT)
        | (rd << MEM_RD_BIT)
        | offset;
    codegen_add_inst(ct, inst);
}

void codegen_mem(struct codegen_table_st *ct, struct parse_node_st *np) {
    codegen_mem_common(
        ct,
        np->stmt.inst.name,
        1, /* always a register  */
        np->stmt.inst.mem.rd,
        np->stmt.inst.mem.rn,
        1, /*up*/
        np->stmt.inst.mem.rm);
}

void codegen_memi(struct codegen_table_st *ct, struct parse_node_st *np) {
    codegen_mem_common(
        ct,
        np->stmt.inst.name,
        0, /* always a register  */
        np->stmt.inst.mem.rd,
        np->stmt.inst.mem.rn,
        1, /*up*/
        np->stmt.inst.mem.rm
    );
}

void codegen_mul(struct codegen_table_st *ct, struct parse_node_st *np) {
    const uint32_t MUL_RD_BIT = 16;
    const uint32_t MUL_RS_BIT = 8;
    const uint32_t MUL_CONST_BIT = 4;

    uint32_t inst = 0;
    inst |= (COND_AL << COND_BIT)
        | (np->stmt.inst.mul.rd << MUL_RD_BIT)
        | (np->stmt.inst.mul.rs << MUL_RS_BIT)
        | (0b1001 << MUL_CONST_BIT)
        | np->stmt.inst.mul.rm;
    codegen_add_inst(ct, inst);
}

int codgen_get_index(struct parse_node_st *np, char * label, int level) {
    int lefti = -1;
    int righti = -1;
    if (np->type == INST) {
        if (!strncmp(label, np->stmt.inst.label, SCAN_TOKEN_LEN)) {
            lefti = level;
        }
    } else if (np->type == SEQ) {
        lefti = codgen_get_index(np->stmt.seq.left, label, level);
        if (np->stmt.seq.left->type != DIR) {
        	++level;
        }
        righti = codgen_get_index(np->stmt.seq.right, label, level);
        if (lefti == -1) {
            lefti = righti;
        }
    }
    return lefti;
}

void codegen_b_common(struct codegen_table_st *ct, char * label, char * name) {
    const uint32_t B_BIT_MASK = 0xffffff;
    const uint32_t B_CONST_BIT = 25;
    const uint32_t B_L_BIT = 24;
    const uint32_t CONST = 0b101;

    int index, start = 0, pcp8 = ct->len + 2,
    delta, l = strcmp(name, "bl") == 0? 1 : 0, offset;
    uint32_t cond = codegen_lookup_bcc(name);
    index = codgen_get_index(ct->tree, label, start);
    delta = (index - pcp8);
    offset = delta & B_BIT_MASK;
    
    uint32_t inst = 0;
    inst = (cond << COND_BIT)
        | (CONST << B_CONST_BIT)
        | (l  << B_L_BIT)
        | offset;
    codegen_add_inst(ct, inst);
}

void codegen_b(struct codegen_table_st *ct, struct parse_node_st *np) {
    codegen_b_common(ct, np->stmt.inst.b.label, np->stmt.inst.name);
}

void codegen_bx(struct codegen_table_st *ct, struct parse_node_st *np) {
    const uint32_t BX_CODE_BIT = 4;
    const uint32_t bx_code = 0b000100101111111111110001;

    uint32_t inst = (COND_AL << COND_BIT)
        | (bx_code << BX_CODE_BIT)
        | np->stmt.inst.bx.rn;
    codegen_add_inst(ct, inst);
}

void codegen_inst(struct codegen_table_st *ct, struct parse_node_st *np) {

    switch (np->stmt.inst.type) {
        case CMP  : codegen_cmp(ct, np); break;
        case CMPI : codegen_cmpi(ct, np); break;
        case MOV  : codegen_mov(ct, np); break; 
        case MOVI : codegen_movi(ct, np); break;
        case DP3  : codegen_dp3(ct, np); break;
        case DP3I : codegen_dp3i(ct, np); break;
        case LS   : codegen_ls(ct, np); break;
        case LSI  : codegen_lsi(ct, np); break;
        case MEM  : codegen_mem(ct, np); break;
        case MEMI : codegen_memi(ct, np); break;
        case MUL  : codegen_mul(ct, np); break;
        case B    : codegen_b(ct, np); break;
        case BX   : codegen_bx(ct, np); break;
        default   : codegen_error("unknown stmt.inst.type");
    }
}

void codegen_stmt(struct codegen_table_st *ct, struct parse_node_st *np) {
    if (np->type == INST) {
        codegen_inst(ct, np);
    } else if (np->type == SEQ) {
        codegen_stmt(ct, np->stmt.seq.left);
        codegen_stmt(ct, np->stmt.seq.right);
    } 
}

void codegen_print(struct codegen_table_st *ct) {
    int i;

    printf("v2.0 raw\n");
    for (i = 0; i < ct->len; i++) {
        printf("%08x\n", ct->table[i]);
    }
}

void codegen_print_hex(struct codegen_table_st *ct) {
    codegen_print(ct);
}

void codegen_print_obj(struct codegen_table_st *ct) {
    codegen_print(ct);
}

void codegen_write(struct codegen_table_st *ct, char *path) {
    int i;
    FILE *obj = fopen(path, "w");

    fprintf(obj, "v2.0 raw\n");
    for (i = 0; i < ct->len; i++) {
        fprintf(obj, "%08x\n", ct->table[i]);
    }
    fclose(obj);
}

void codegen_elf_write(struct codegen_table_st *ct, char *path) {
    int i;
    elf_context elf;
    struct codegen_label_pair *pl;
    int binding;

    elf_init(&elf);
    for (i = 0; i < ct->label_count; i++) {
        pl = &ct->labels[i];
        if (codegen_is_public_label(ct, pl)) {
            binding = STB_GLOBAL;
        } else {
            binding = STB_LOCAL;
        }
        elf_add_symbol(&elf, pl->label, pl->offset, binding);
    }
    for (i = 0; i < ct->len; i++) {
        elf_add_instr(&elf, ct->table[i]);
    }

    FILE *f = fopen(path, "w");
    if (!f) {
        perror(path);
        return;
    }
    if (!elf_write_file(&elf, f)) {
        printf("elf_write_file failed\n");
    }
    fclose(f);
}

void codegen_hex_write(struct codegen_table_st *ct, struct parse_node_st *np, char *path) {
    np++; np--; /* why is this passed in if it is never used? */
    codegen_write(ct, path);
}

void codegen_obj_write(struct codegen_table_st *ct, struct parse_node_st *np, char *path) {
    np++; np--; /* why is this passed in if it is never used? */
    codegen_elf_write(ct, path);
}
