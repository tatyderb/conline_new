#include <stdio.h>
#include <assert.h>

float fahr(int cel)
{
    float res;
    // тут нужно написать код
    res = (cel * 1.8) + 32;
    return res;
}

int main()
{
    int cel;    // градусы Цельсия
    float f;    // градусы Фаренгейта
    
    // тест
    /*
    cel = 0;
    f = fahr(cel);
    printf("C = %d, F = %.2f\n", cel, f);
    */
        // тесты
    assert(32 == fahr(0));
    assert(122 == fahr(50));
    assert(-40 == fahr(-40));
    printf("C = %d, F = %.2f\n", 1, fahr(1));
    assert(33.8 == fahr(1));

    
    // для произвольного числа
    scanf("%d", &cel);
    f = fahr(cel);
    printf("C = %d, F = %.2f\n", cel, f);
    
    return 0;
}