//system resources
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
//personal resources
#include "map.h"
//globals
#define USED_ARGS 2
#define PROGRAM 1
//usage
void
usage(void)
{
	printf("Program expects:\n$ replace input_file output_file key1 value1 [key 2 value2 ...]\n");
	exit(-1);
}
//prototypes
int replace(int argc, char** argv);
void add_mappings(int argc, char** argv, struct map_st * map);
bool is_word_char(char ch);
int replace_text(char* input, char* output, struct map_st * map);
//methods
int
main(int argc, char** argv)
{
	if (argc < (PROGRAM + USED_ARGS))
		usage();
		
	int arg_start = PROGRAM;
	if (replace(argc-arg_start, &argv[arg_start]) < 0)
		usage();
		
	return 0;
}

int 
replace(int argc, char** argv)
{
	if (argc == 2 || argc % 2 != 0) 
		usage();

	struct map_st map;
	map_init(&map);
	add_mappings(argc - USED_ARGS, &argv[USED_ARGS], &map);

	int input = 0, output = 1;
	if(replace_text(argv[input], argv[output], &map) < 0)
		return -1;
		
	return 0;
}

void
add_mappings(int argc, char** argv, struct map_st * map)
{
	int arg;
	for (arg = 0; arg < argc; arg += 2)
		map_add(map, argv[arg], argv[arg+1]);
}

bool is_word_char(char ch) {
    return ch != ' ' && ch != '\t' && ch != '\n';
}

int 
replace_text(char* input, char* output, struct map_st * map)
{
	FILE *ipf, *opf;
	char word[MAP_KEY_LEN + 1] = { 0 };
	char * value;
	char ch;
	bool in_word = false;
	int count = 0, stat = 0;
	//check if both files can be opened at once
	if ( !(ipf = fopen(input, "r")) || !(opf = fopen(output, "w")) )
		return -1;
	//write to file
	do
	{
		//read a char
		if (!fread(&ch, sizeof(char), 1, ipf))
		{
			//non overflowing word(s) at the end or beginning of a file that aren't written because of not having a whitespace after them //can check using nano
			if (count) //safety edge case that may occur
				fwrite(&word, sizeof(char), count, opf);
			break;
		}
		//write complete whitespace word to file
		if (in_word && !is_word_char(ch) && count <= MAP_KEY_LEN)
		{
			if ((value = map_lookup(map, word)))
			{
				count = strlen(value);
				strncpy(word, value, count);
				word[count] = '\0';
			}
			fwrite(&word, sizeof(char), count, opf);
			//reset buffer and count
			memset(word, 0, MAP_KEY_LEN);
			count = 0;
		}
		//write overflowing word to file since it is not whitespace seperated by accepted length
		if (in_word && is_word_char(ch) && count == MAP_KEY_LEN)
		{
			fwrite(&word, sizeof(char), count, opf);
			//reset
			memset(word, 0, MAP_KEY_LEN);
			count = 0;
			//write current word char to file
			fwrite(&ch, sizeof(char), 1, opf);
			//write the rest of the overflowing word to file until we hit whitespace
			while ((stat = fread(&ch, sizeof(char), 1, ipf)) && is_word_char(ch))
				fwrite(&ch, sizeof(char), 1, opf);
			//wrote overflowing characters up to the end of file
			if (!stat)
				break;
			//reached whitespace
		}
		//update word status
		in_word = is_word_char(ch);
		//add new word char to buffer
		if (in_word && count != MAP_KEY_LEN)
		{
			word[count++] = ch;
			word[count] = '\0';
		}
		//write any whitespace to file
		if(!in_word)
			fwrite(&ch, sizeof(char), 1, opf);
		//repeat process as much as necessary
	} while (true);
	//close files
	fclose(ipf);
	fclose(opf);
	//return 0 for success
	return 0;
}
