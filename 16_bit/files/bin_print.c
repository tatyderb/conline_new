#include <stdio.h>

#define BYTESIZE 8        // считаем, что в байте 8 бит

void print_bin(unsigned char x, char end);

int main()
{
    char x;
    scanf("%hhu", &x);      // hh используеся для указания, что работа с char
    
    print_bin(x, '\n');
    
    return 0;
}

void print_bin(unsigned char x, char end)
{
    char a[BYTESIZE+1] = {};
    
    for(int i = BYTESIZE-1; x > 0 && i >= 0; i--) {
        a[i] = x % 2;
        x = x / 2;
    }
    for(int i = 0; i < BYTESIZE; i++)
        printf("%d", a[i]);
    if (end)
        printf("%c", end);
}
