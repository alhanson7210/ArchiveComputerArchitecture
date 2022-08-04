int search_c(int *arr, int left, int right, int x) {
    int mid;

    if (right < left) {
        return -1;
    }

    mid = left + ((right - left) / 2);
    if (arr[mid] == x) {
        return mid;
    } else if (arr[mid] > x) {
        return search_c(arr, left, mid - 1, x);
    } else {
        return search_c(arr, mid + 1, right, x);
    }
}
