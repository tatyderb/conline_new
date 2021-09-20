#include <stdio.h>

int main()
{
    int hour;  // часы
    int min;   // минуты
    int sec;   // секунды

    scanf("%d", &hour);
    scanf("%d", &min);
    
    min = hour * 60 + min;  // сохраним результат в ту же переменную min
    sec = min * 60;         // этот результат используем в следующих вычислениях

    printf("%d\n", min);
    printf("%d\n", sec);    
    
    return 0;
}