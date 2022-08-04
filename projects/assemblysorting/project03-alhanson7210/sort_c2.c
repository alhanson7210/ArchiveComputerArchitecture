int find_max_index_c2(int *array, int len)
{
    int i;
    int max = array[0];
    int index = 0;

    for (i = 1; i < len; i++) {
        if (array[i] > max) {
            max = array[i];
            index = i;
        }
    }
    return index; 
}

int sort_c2(int *array, int len)
{
    int i;
    int max_index;
    int tmp;

    for (i = 0; i < len; i++) {
        max_index = find_max_index_c2(&array[i], len - i) + i;
        if (max_index != i) {
            tmp = array[i];
            array[i] = array[max_index];
            array[max_index] = tmp;
        }
    }
    return len;
}
