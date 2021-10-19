#include <stdio.h>

#define min(a,b) ((a)<(b) ? (a) : (b))

int main()
{
    int n,  // страниц
        gems = 0;   // всего цифр

    scanf("%d", &n);
    
    int base = 9;
    int i = 1;      // i-значные цифры
    while(1){
        int d = min(base, n);
        gems += d*i;
        n -= d;
        printf("i=%d base=%d n=%d d=%d gems=%d\n", i, base, n, d, gems);
        if (n == 0) {
            break;
        }
        i++;
        base *= 10;
    }
    printf("%d %d\n", i, gems);
    
    return 0;
}