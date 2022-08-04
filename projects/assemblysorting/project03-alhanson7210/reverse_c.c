#include <string.h>

void reverse_c(char *buf) {
    char *end;
    char btmp, etmp;

    /* find a ptr to the last non-null char */
    end = buf;
    while(*end != '\0') {
        end++;
    }
    end--;

    while (buf < end) {
        btmp = *buf;
        etmp = *end;
        *buf = etmp;
        *end = btmp;
        buf += 1;
        end -= 1;
    }
}
