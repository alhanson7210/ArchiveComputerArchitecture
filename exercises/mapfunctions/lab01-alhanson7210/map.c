#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"

//map implementaton
void 
map_init(struct map_st* map)
{
	int i;
	map->count = 0;
	for (i = 0; i < MAP_TABLE_LEN; i++)
	{
		map->table[i].key[0] = 0;
		map->table[i].value[0] = 0;
	}
}

void 
map_add(struct map_st* map, char* key, char* value)
{
	if (map->count != MAP_TABLE_LEN)
	{
		strncpy(map->table[map->count].key, key, MAP_KEY_LEN);
		int key_len = strlen(map->table[map->count].key);
		if (map->table[map->count].key[key_len] != '\0')
			map->table[map->count].key[key_len] = '\0';

		strncpy(map->table[map->count].value, value, MAP_VALUE_LEN);
		int value_len = strlen(map->table[map->count].value);
		if (map->table[map->count].value[value_len] != '\0')
			map->table[map->count].value[value_len] = '\0';

		map->count++;
	}
}

char* 
map_lookup(struct map_st* map, char* key)
{
	if (!map || map->count < 1) 
		return 0;
		
	int mapping;
	for (mapping = 0; mapping < map->count; mapping++)
	{
		if (strncmp(map->table[mapping].key, key, MAP_KEY_LEN) != 0)
			continue;
			
		return map->table[mapping].value;
	}

	return 0;
}
