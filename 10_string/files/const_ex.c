#include <stdio.h>

int main() {
    const int x = 12;
    x = 34;
    
    char a[100] = "hello";
    const char * a1 = a;
    a1 = a1 + 2;
    a1[2] = 'q';
    printf("a=%s a1=%s\n", a, a1);
    
    char b[100] = "hello";
    char const * b1 = b;
    b1 = b1 + 2;
    b1[2] = 'q';
    printf("b=%s b1=%s\n", b, b1);
    
    char s[100] = "hello";
    char * const s1 = s;
    s1 = s1 + 2;
    s1[2] = 'q';
    printf("s=%s s1=%s\n", s, s1);

    return 0;
}