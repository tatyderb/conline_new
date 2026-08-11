#include <stdio.h>

int *foo()
{
    int a = 42;
    return &a;
}

int main()
{
    int * p = foo();
    printf("%p %d\n", p, *p);
    return 0;
}
