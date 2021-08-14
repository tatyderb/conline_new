#include <stdio.h>

int main()
{
    int x, y;   // объявили переменные x и y типа int
    
    scanf("%d", &x);    // ввели число и записали его в х
    scanf("%d", &y);    // ввели число и записали его в y
    int res;            // объявили переменную res типа int
    res = x + y;        // результат вычисления x+y записали в res/
    printf("%d + %d = %d\n", x, y, res);    // печатаем ответ
    return 0;
}
