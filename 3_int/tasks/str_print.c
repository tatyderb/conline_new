#include <stdio.h>

int main()
{
    // числа по разным форматам
    printf("<%4d>\n", 12);         // <  12>      
    printf("<%-4d>\n", 12);        // <12  >      
    
    // пробуем печать строки по разным форматам
    printf("<%5s>\n", "abc");         // <  abc>      
    printf("<%05s>\n", "abc");        // <  abc>     
    printf("<%-5s>\n", "abc");        // <abc  >
    printf("<%5s>\n", "abcdefgh");    // <abcdefgh>
    printf("<%.5s>\n", "abcdefgh");   // <abcde>
    printf("<%.5s>\n", "abc");        // <abc>
    
    return 0;
}