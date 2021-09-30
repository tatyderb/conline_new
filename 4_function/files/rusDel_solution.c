#include <stdio.h>

int rusDel(int a, int b);

int main()
{
    int a, b;
    scanf("%d%d", &a, &b);
    printf("%d\n", rusDel(a, b));
    return 0;
}

int rusDel(int a, int b)
{
    if (b == 1)
        return a;
    
    int a_new=0, mult=0, rem=0; // чтобы не было предупреждения, 
                                // что они используются не инициализированными
    if (a % 2 == 0) {
        a_new = a / 2;
        mult = 2;
        rem = 0;
    } else {
        a_new = a - b;
        mult = 1;
        rem = 1;
    }
    if (a_new == 0) {
        printf("1\n");
        return 1;
    }
    printf("%d %d %d\n", a_new, mult, rem);
    
    int part = rusDel(a_new, b);
    int new_part = part * mult + rem;
    printf("%d * %d + %d = %d\n", part, mult, rem, new_part);
    
    return new_part;
}

