#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <string.h>
int main() {
    char str[256];
    int n;
    scanf("%d", &n);
    while (n--) {
        gets(str);
        puts(str);
    }
    return 0;
}

