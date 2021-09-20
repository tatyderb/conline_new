#include <stdio.h>

/* объявили функцию с именем foo (сами придумали),
Она принимает один аргумент типа float
и возвращает результат типа float
*/
float foo(float x)
{
    float res;
    res = x*x + 2*x + 3;
    return res;     // вернули значение, посчитанное в функции
}

// main - тоже функция, она воз
int main()
{
    float z;
    z = foo(0);    // вызвали функцию foo для x=0
    printf("f(%f) = %f\n", 0., z);
    
    z = foo(1);    // вызвали функцию foo для x=1
    printf("f(%f) = %f\n", 1., z);
    
    float a;
    scanf("%f", &a);
    z = foo(a);   // вызвали функцию foo для x=a
    printf("f(%f) = %f\n", a, z);
    
    return 0;
}
