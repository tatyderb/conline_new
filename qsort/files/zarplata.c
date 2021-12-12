#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define N 100

typedef struct {
    int base;   // ставка   
    int prem;   // премия
    int sum;    // зарплата всего = ставка + премия
} Zarplata;

int cmp_zarplata(const void * p1, const void * p2)
{
    // а и b указатели на зарплату
    const Zarplata * a = (const Zarplata *)p1;  
    const Zarplata * b = (const Zarplata *)p2;
    
    // если суммы разные, сравниваем только суммы
    if (a->sum != b->sum)
        return (a->sum < b->sum) - (a->sum > b->sum);
    
    // если дошли сюда, то тут суммы одинаковые, нужно сравнить base
    return (a->base < b->base) - (a->base > b->base);
}

int main()
{
    int n, i;
    Zarplata a[N];
    
    scanf("%d", &n);
    for(i = 0; i < n; i++) {
        scanf("%d%d", &a[i].base, &a[i].prem);
        a[i].sum = a[i].base + a[i].prem;       // вычислим один раз при чтении
    }
    
    qsort(a, n, sizeof(Zarplata), cmp_zarplata);
    
    for(i = 0; i < n; i++) {
        printf("%d %d %d\n", a[i].base, a[i].prem, a[i].sum);
    }
    
    return 0;
}