#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
    char *s = NULL;
    
    while(1 == scanf("%ms", &s)) {
        printf("<%s>\n", s);
      
        free(s);
    }
    
    int c;
    c = 'a';
    printf("%c %d %d\n", c, c, isalnum(c));
    c = '0';
    printf("%c %d %d\n", c, c, isalnum(c));
    c = '_';
    printf("%c %d %d\n", c, c, isalnum(c));
    return 0;
}