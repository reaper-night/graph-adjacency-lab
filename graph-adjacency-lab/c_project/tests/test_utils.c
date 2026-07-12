#include <stdio.h>
#include "../include/utils.h"

int main() {
    int passed = 0;
    int total = 0;

    total++;
    if (utils_add(2, 3) == 5) passed++;
    else printf("FAIL: utils_add(2, 3) != 5\n");

    total++;
    if (utils_subtract(5, 3) == 2) passed++;
    else printf("FAIL: utils_subtract(5, 3) != 2\n");

    total++;
    if (utils_multiply(4, 5) == 20) passed++;
    else printf("FAIL: utils_multiply(4, 5) != 20\n");

    total++;
    if (utils_divide(10, 2) == 5) passed++;
    else printf("FAIL: utils_divide(10, 2) != 5\n");

    total++;
    if (utils_divide(10, 0) == 0) passed++;
    else printf("FAIL: utils_divide(10, 0) != 0\n");

    total++;
    int a = 10, b = 20;
    utils_swap(&a, &b);
    if (a == 20 && b == 10) passed++;
    else printf("FAIL: utils_swap failed\n");

    total++;
    if (utils_max(5, 10) == 10) passed++;
    else printf("FAIL: utils_max(5, 10) != 10\n");

    total++;
    if (utils_min(5, 10) == 5) passed++;
    else printf("FAIL: utils_min(5, 10) != 5\n");

    printf("Tests: %d/%d passed\n", passed, total);
    return (passed == total) ? 0 : 1;
}