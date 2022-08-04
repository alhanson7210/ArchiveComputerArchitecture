/* LIBRARIES */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
/* GLOBAL REFERENCES */
#define ERROR -1
#define DEFAULT 0
#define SUCCESS 0
#define XPOS 0
#define SEARCH_USED 1
#define USED 2
#define PROGRAM 1
#define REVERSE_LIMIT 1
#define REQUIRED 3 
#define INPUT_LIMIT 128
#define MAX_PATH 256
/* ENUMERATIONS */
enum numbers {ZERO, ONE};
/* REVERSE CODE & MAIN */
void reverse_c(char * buf);
void reverse_s(char * buf);
void reverse(int argc, char ** argv); // MAIN FUNCTION
/* SEARCH CODE & MAIN */
int search_c(int * arr, int left, int right, int x);
int search_s(int * arr, int left, int right, int x);
void search(int argc, char ** argv); // MAIN FUNCTION
/* SORT CODE AND MAIN */
//int find_max_index_c(int *array, int len); // wasn't sure if I needed this or not but I added it just in case
//int find_max_index_s(int *array, int len); // added the .global so this works correctly if call in here directly
int sort_c(int * array, int len);
int sort_s(int * array, int len);
void sort(int argc, char ** argv); // MAIN FUNCTION
/* SORT_S2 CODE AND MAIN */
//int find_max_index_c2(int *array, int len); // wasn't sure if I needed this or not but I added 
//int find_max_index_s2(int *array, int len); // added the .global so this works correctly
//int sort_c2(int * array, int len);
//int sort_s2(int * array, int len);
//void sort2(int argc, char ** argv); // MAIN FUNCTION
/* HANDLE ERRORS */
void error(void) {
    printf("usage: ./project03 <program> ...\n");
    exit(ERROR);
}
/* DRIVER */
int main(int argc, char ** argv) {
    if (argc < REQUIRED) // AT LEAST ONE ARG
        error();
    
    char progname[MAX_PATH] = { DEFAULT };
    strncpy(progname, argv[PROGRAM], MAX_PATH);
    
    if (strcmp(progname, "reverse") == SUCCESS)
        reverse(argc - USED, &argv[USED]);
    else if (strcmp(progname, "search") == SUCCESS)
        search(argc - USED, &argv[USED]);
    else if (strcmp(progname, "sort") == SUCCESS)
        sort(argc - USED, &argv[USED]);
    // else if (strcmp(progname, "sort2") == SUCCESS) extra credit
        // sort2(argc - USED, &argv[USED]);
    
    return SUCCESS;
}

void reverse(int argc, char ** argv)
{
    if (argc > REVERSE_LIMIT)
        error();
    
    char output_c[MAX_PATH] = { DEFAULT };
    char output_s[MAX_PATH] = { DEFAULT };
    strncpy(output_c, *argv, MAX_PATH);
    strncpy(output_s, *argv, MAX_PATH);
    
    reverse_c(output_c);
    printf("C: %s\n", output_c);
    reverse_s(output_s);
    printf("Assembly: %s\n", output_s);
}

void search(int argc, char ** argv)
{
    if (argc-SEARCH_USED > INPUT_LIMIT)
        error();
    
    int idx,
    idx_c,
    idx_s,
    left = DEFAULT,
    x = atoi(argv[XPOS]), // number to search
    arr_size = argc-SEARCH_USED, // size of int array
    right = arr_size-ONE,
    arr[arr_size]; // arr
    argv++;
    
    for (idx = DEFAULT; idx < arr_size; idx++)
        arr[idx] = atoi(argv[idx]);
    
    idx_c = search_c(arr, left, right, x);
    printf("C: %d\n", idx_c);
    idx_s = search_s(arr, left, right, x);
    printf("Assembly: %d\n", idx_s);
}

void sort_p(const char * name, int * array, int len)
{
    int idx;
    printf("%s:", name);
    for (idx = DEFAULT; idx < len; idx++)
        printf(" %d", array[idx]);
    printf("\n");
}

void sort(int argc, char ** argv)
{
    if (argc > INPUT_LIMIT)
        error();
    
    int idx,
    len = argc,
    len_c,
    len_s,
    array_c[len],
    array_s[len];

    for (idx = DEFAULT; idx < len; idx++)
    {
        array_c[idx] = atoi(argv[idx]);
        array_s[idx] = atoi(argv[idx]);
    }

    len_c = sort_c(array_c, len);
    sort_p("C", array_c, len_c);
    len_s = sort_s(array_s, len);
    sort_p("Assembly", array_s, len_s);
}

// void sort2(int argc, char ** argv) works, just commented out extra credit for project04
// {
    // if (argc > INPUT_LIMIT)
        // error();
    // 
    // int idx,
    // len = argc,
    // len_c,
    // len_s,
    // array_c[len],
    // array_s[len];
// 
    // for (idx = DEFAULT; idx < len; idx++)
    // {
        // array_c[idx] = atoi(argv[idx]);
        // array_s[idx] = atoi(argv[idx]);
    // }
// 
    // printf("--Extra Credit--\n");
    // len_c = sort_c2(array_c, len);
    // sort_p("C", array_c, len_c);
    // len_s = sort_s2(array_s, len);
    // sort_p("Assembly", array_s, len_s);
    // printf("--Extra Credit--\n");
// }
