#include <stdio.h>

int main()
{
    int h = 2, m = 3;
    // printf("\e[1;31mВведите количество часов: \e[0m");
    scanf("%d", &h);
    // printf("\e[1;31mВведите количество минут: \e[0m");
    scanf("%d", &m);
    // printf("\e[1;31mВсего в минутах %d минут\e[0m\n", h * 60 + m);
    // printf("\e[1;31mВсего в секундах %d секунд\e[0m\n", (h * 60 + m) * 60);
    printf("\e[1;31m%d\e[0m\n", h * 60 + m);
    printf("\e[1;31m%d\e[0m\n", (h * 60 + m) * 60);
    
    
    return 0;
}
    