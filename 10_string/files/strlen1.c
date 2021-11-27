#include <stdio.h>
#include <string.h>

size_t mystrlen(const char *s) {
    int i;
    for (i = 0; s[i] != '\0'; i++)
        ;                          // делать в цикле ничего не нужно, пустое тело цикла
    return i;
}
int main() {
    char * s = "abc";
    printf("%zd\n", strlen(s));     // эталонная функция
    printf("%zd\n", mystrlen(s));   // наша функция
    return 0;
}
