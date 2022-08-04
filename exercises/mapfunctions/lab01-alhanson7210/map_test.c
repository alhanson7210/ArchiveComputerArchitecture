#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "map.h"

int 
main(int argc, char **argv)
{
    struct map_st map;
    char *value;
    char *key;

    map_init(&map);

    map_add(&map, "course", "cs315");
    map_add(&map, "year", "2020");
    map_add(&map, "term", "fall");

    key = "year";
    value = map_lookup(&map, key);

    if (value) {
        printf("key = %s, value = %s\n", key, value);
    } else {
        printf("key = %s not found\n", key);
    }

    key = "section";
    value = map_lookup(&map, key);

    if (value) {
        printf("key = %s, value = %s\n", key, value);
    } else {
        printf("key = %s not found\n", key);
    }

    return 0;
}
