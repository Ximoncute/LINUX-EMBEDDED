#include <stdio.h>
#include "strutils.h"

int main() {
    char str1[] = "  Hello World!  ";
    char str2[] = "abcdef";
    const char *numstr = "12345";
    int num;

    printf("Before trim: '%s'\n", str1);
    str_trim(str1);
    printf("After trim: '%s'\n", str1);

    printf("Before reverse: '%s'\n", str2);
    str_reverse(str2);
    printf("After reverse: '%s'\n", str2);

    if (str_to_int(numstr, &num))
        printf("Converted '%s' to %d\n", numstr, num);
    else
        printf("Failed to convert '%s'\n", numstr);

    return 0;
}
