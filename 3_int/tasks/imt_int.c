#include <stdio.h>

struct A {
    float m;
    int h;
} a [] = {
    {45, 150},
    {83, 175},
    {73.124, 100},
    {73.124, 90},
    {0, 90},
    {134.67, 218}
};

int main()
{
    float m;    // масса, кг 
    int   hsm;  // рост, см
    
    
    //scanf("%f%d", &m, &hsm);    // читаем входные данные
    for (int i = 0; i < sizeof(a)/sizeof(a[0]); i++){
        m = a[i].m;
        hsm = a[i].h;
        float h1 = hsm / 100.;
        printf("m=%f h=%d exp=%f -> ", m, hsm, m/(h1*h1));
    
        float h = hsm / 100;        // рост в метрах
        
        
        float imt = m / (h * h);    // индекс массы тела (формула Кетле)

        printf("%f\n", imt);
    }
    
    return 0;
}
