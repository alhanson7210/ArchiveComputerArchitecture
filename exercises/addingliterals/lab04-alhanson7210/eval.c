#include "ntcalc.h"

unsigned int eval_tree(struct parse_node_st *np)
{
    unsigned int retval = 0;
    unsigned int r = 0;
    unsigned int l = 0;

    switch (np->type) {
        case EX_INTVAL:
            retval = np->intval.value;
            break;
        case EX_OPER1:
            retval = eval_tree(np->oper1.expr);
            if (np->oper1.oper == OP_MINUS)
            {
                retval = -retval;
            }
            else if (np->oper1.oper == OP_BWNOT)
            {
            	retval = ~retval;
            }
            else
            {
                printf("unsupported unary operator\n");
            }
            break;
        case EX_OPER2:
            r = eval_tree(np->oper2.right);
            l = eval_tree(np->oper2.left);
            switch (np->oper2.oper) {
                case OP_PLUS:
                    retval = l + r;
                    break;
                case OP_MINUS:
                    retval = l - r;
                    break;
                case OP_MULT:
                    retval = l * r;
                    break;
                case OP_DIV:
                    retval = l / r;
                    break;
                case OP_LSHIFT:
                	retval = l << r;
                	break;
                default:
                	break;
            }
            break;
    }
    return retval;
}

char digits[] = "0123456789ABCDEF";

void 
eval_print(unsigned int result, int width, int base)
{
	int bitlen = 1 + 2 + width;
	char bitarray[bitlen];
	char * b_a;
	int bitNum[32];
	int i, j, k, l, len;
	
	switch (base)
	{
		case 2:
			bitarray[0] = '0';
			bitarray[1] = 'b';
			b_a = &bitarray[2];
			//calculate bits from first to last bit by using the remainder to obtain 1's and 0's
			i = 0;
			while (result > 0)
			{
				bitNum[i++] = result % base;
				result = result / base;
			}
			//place zeros for unused bits
			len = width - i;
			l = len;
			while(--l >= 0)
			{
				b_a[l] = '0';
			}
			//grab and print from last bit to the first bit
			k = len;
			j = i;
			while(--j >= 0)
			{
				b_a[k++] = digits[bitNum[j]];
			}
			b_a[k] = '\0';
			break;
		case 10:
			printf("%d\n", result);
			return;
			break;
	}
	
	printf("%s\n", bitarray);
	return;
}

int
power(int base, int exp)
{
	if (exp <= 0)
		return 1;
		
	int n = 1, 
	i = exp;
	while(i != exp)
	{
		n *= base;
	}
	return n;
}
