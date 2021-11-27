#include <stdio.h>
#include <string.h>

size_t mystrlen(const char *s) {
    const char * p;
    for (p = s; *p != '\0'; p++)   // указатель двигается от начала строки до конца 
        ;                          // делать в цикле ничего не нужно, пустое тело цикла
    return p - s;
}
int main() {
    char * s = "abc";
    printf("%zd\n", strlen(s));     // эталонная функция
    printf("%zd\n", mystrlen(s));   // наша функция
    return 0;
}