# lab01-alhanson7210
lab01-alhanson7210 created by GitHub Classroom
> Due Monday, August 24th at 11:59pm in your lab GitHub repo.

Requirements
> Write a "mail merge" program which can replace designated labels in text file with string values. For example:
```
$ cat form.txt

My name is FIRST LAST

I live in CITY

$ ./replace form.txt complete.txt FIRST John LAST Smith CITY Sacramento

$ cat complete.txt

My name is John Smith

I live in Sacramento
```
The usage is:
```
$ replace input_file output_file key1 value1 [key 2 value2 ...]
```
In order to implement the replace program you will need implement a simple map implementation in C that will allow you to look up a value with a given key, like a dictionary in Python. However will implement a very simple version. Here are the data types and functions that map implementation should use and implement:

map.h
```
#ifndef _MAP_H
#define _MAP_H

#define MAP_KEY_LEN 64
#define MAP_VALUE_LEN 64
#define MAP_TABLE_LEN 128

struct map_pair_st {
    char key[MAP_KEY_LEN];
    char value[MAP_VALUE_LEN];
};

struct map_st {
    struct map_pair_st table[MAP_TABLE_LEN];
    int count;

};

void map_init(struct map_st *map);
void map_add(struct map_st *map, char *key, char *value);
char * map_lookup(struct map_st *map, char *key);

#endif
```
Here is an example test program for the map implementation:
```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "map.h"

int main(int argc, char **argv) {
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
```
We will work on the implementation of the map functions in lab section.

Given
Your instructor will show sample code which demonstrates techniques you will use to write replace

A simple word count program which reads and writes files using the C library functions fopen(), fread(), fwrite() and fclose()

Important: your implementation must use a FILE struct and the "f" functions for file I/O. You must also use your implementation of the map functions described above.

Greg: 

Phil: https://github.com/cs-315-03-20f/inclass

What to turn in
Collaboration: You may collaborate with classmates in lab or after, but please hand in your own working implementation of replace.c

Due: End of day on Monday August 24th at 11:59pm.

GitHub: Please create a repo under the lab project for your section:

Greg: 

Phil: https://classroom.github.com/a/hns8bssz
