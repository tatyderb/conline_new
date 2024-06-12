#include <stdio.h>

#define min(a,b) ((a)<(b) ? (a) : (b))

int main()
{
    unsigned long long int n;          // страниц
    unsigned long long int gems = 0;   // всего цифр

    scanf("%llu", &n);
    
    unsigned long long  int base = 9;     // сколько чисел длины len
    unsigned long long  int len = 1;      // длина чисел
    int counter;                          // счетчик циклов
    for (counter = 0; n > 0; counter++)
    {   
        unsigned long long int d = min(base, n);
        gems += d * len;
        n -= d;
        // printf("len=%llu base=%llu n=%llu d=%llu gems=%llu\n", len, base, n, d, gems);
        len++;
        base *= 10;
    }
    printf("%d %llu\n", counter - 1, gems);
    
    return 0;
}
