#ifdef AAA
#include <stdio.h>

void simpleFactors(unsigned int a, unsigned int last, unsigned int n);

int main()
{
    unsigned int a;
    scanf("%u", &a);
    simpleFactors(a, 2, 0);
    
    return 0;
}
#endif
void printFactor(unsigned int last, unsigned int n)
{
    if (n == 0)
        return;
    if (n == 1)
        printf("%u ", last);
    else
        printf("%u^%u ", last, n);
}

void simpleFactors(unsigned int a, unsigned int last, unsigned int n)
{
    printf("a=%u last=%u n=%u\n", a, last, n);
    if (a == 1) {
        printFactor(last, n);
        return;
    }
    
    if (a % last == 0)
        simpleFactors(a/last, last, n+1);
    else {
        simpleFactors(a, last+1, 0);
        printFactor(last, n);
    }
}
