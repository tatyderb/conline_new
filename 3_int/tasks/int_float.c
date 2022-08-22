#include <stdio.h>

int main()
{
    float z = 0.375;
    int x = 32;
    
    printf("Печатаю int правильно: \t x=%d\n", x);
    printf("Печатаю int не правильно: \t x=%f\n", x);

    printf("Печатаю float правильно: \t z=%f\n", z);
    printf("Печатаю float не правильно: \t z=%d\n", z);
    
    return 0;
}
