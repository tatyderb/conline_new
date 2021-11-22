#include <stdio.h>

int main()
{
    int n;      // сколько чисел
    int a[100]; // числа
    int i;
    
    scanf("%d", &n);
    // читаем числа и сохраняем в массив
    for(i = 0; i < n; i++)
        scanf("%d", &a[i]);
    
    // печатаем сохраненные числа через пробел
    for(i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
    
    return 0;
}
    