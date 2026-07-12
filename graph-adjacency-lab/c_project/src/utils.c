#include "utils.h"

int utils_add(int a, int b) {
    return a + b;
}

int utils_subtract(int a, int b) {
    return a - b;
}

int utils_multiply(int a, int b) {
    return a * b;
}

int utils_divide(int a, int b) {
    if (b == 0) {
        return 0;
    }
    return a / b;
}

void utils_swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int utils_max(int a, int b) {
    return (a > b) ? a : b;
}

int utils_min(int a, int b) {
    return (a < b) ? a : b;
}