#include "utils.h"
#include <stdio.h>

int utils_add(int a, int b) {
    return a + b;
}

void print_array(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}