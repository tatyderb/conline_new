#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define N 100

typedef struct {
    int base;   // ставка   
    int prem;   // премия
} Zarplata;

int cmp_zarplata(const void * p1, const void * p2)
{
    // а и b указатели на зарплату
    const Zarplata * a = (const Zarplata *)p1;  
    const Zarplata * b = (const Zarplata *)p2;
    
    int a_sum = a->base + a->prem;
    int b_sum = b->base + b->prem;
    
    // если суммы разные, сравниваем только суммы
    if (a_sum != b_sum)
        return (a_sum < b_sum) - (a_sum > b_sum);
    
    // если дошли сюда, то тут суммы одинаковые, нужно сравнить base
    return (a->base < b->base) - (a->base > b->base);
}

int main()
{
    int n, i;
    Zarplata a[N];
    
    scanf("%d", &n);
    for(i = 0; i < n; i++)
        scanf("%d%d", &a[i].base, &a[i].prem);
    
    // отладочная печать, проверяем, что прочитали данные верно
    for(i = 0; i < n; i++)
        printf("%d %d\n", a[i].base, a[i].prem);
    
    qsort(a, n, sizeof(Zarplata), cmp_zarplata);
    
    for(i = 0; i < n; i++)
        printf("%d %d %d\n", a[i].base, a[i].prem, a[i].base + a[i].prem);
    
    return 0;
}