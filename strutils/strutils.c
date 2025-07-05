#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "strutils.h"

void str_reverse(char *str) {
    if (!str) return;
    int len = strlen(str);
    for (int i = 0; i < len / 2; ++i) {
        char tmp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = tmp;
    }
}

void str_trim(char *str) {
    if (!str) return;
    int start = 0, end = strlen(str) - 1;

    // Trim leading spaces
    while (isspace((unsigned char)str[start])) start++;
    
    // Trim trailing spaces
    while (end > start && isspace((unsigned char)str[end])) end--;

    // Shift string
    int i = 0;
    while (start <= end) {
        str[i++] = str[start++];
    }
    str[i] = '\0';
}

int str_to_int(const char *str, int *out_num) {
    if (!str || !out_num) return 0;
    char *endptr;
    long val = strtol(str, &endptr, 10);

    if (*endptr != '\0') return 0;

    *out_num = (int)val;
    return 1;
}
