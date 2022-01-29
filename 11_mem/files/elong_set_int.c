#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    char * a;        // number is a[0]*10^0 + a[1]*10^1 + ..+ a[n]*10^n
    unsigned int n;  // наибольшая степень десяти
    size_t  size;    // размер массива a
}Decimal;

void elong_print (Decimal * p)
{
    int i;
    for (i = (unsigned int)p->n; i>=0; i--)
        printf("%d", p->a[i]);
    printf("\n");
}
void elong_check(Decimal * p)
{
    unsigned int i;
    for (i=0; i <= p->n; i++)
        if (p->a[i] > 9 || p->a[i] < 0) {
            printf("ERROR: a[%d]=%d\n", i, p->a[i]);
        }
}
void elong_set_int(Decimal * px, unsigned int number)
{
    if (number == 0){       // 0*10**0
        px->size = 1;
        px->n = 0;
        px->a = malloc(px->size);
        px->a[0] = 0;
        return;
    }

    // number точно меньше 10 в 100, выделим память с запасом
    px->size = 100;
    px->a = malloc(px->size);
    
    
    for(px->n = 0; number > 0; px->n++){
        px->a[px->n] = number % 10;
        number /= 10;
    }
    px->n --;
    
    px->size = px->n + 1;
    px->a = realloc(px->a, px->size);
}
void elong_destroy(Decimal * px)
{
    free(px->a);
}

int main()
{
    Decimal x;
    elong_set_int(&x, 147);
    elong_print(&x);
    elong_check(&x);
    elong_destroy(&x);
    
    elong_set_int(&x, 654321);
    elong_print(&x);
    elong_check(&x);
    elong_destroy(&x);
    
    elong_set_int(&x, 7);
    elong_print(&x);
    elong_check(&x);
    elong_destroy(&x);
    
    elong_set_int(&x, 0);
    elong_print(&x);
    elong_check(&x);
    elong_destroy(&x);
    
    return 0;
}
