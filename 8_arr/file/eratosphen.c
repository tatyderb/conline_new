#include <stdio.h>

#define MAX_PRIME 1300001

// заполняем массив 0, это простые числа
// потом будем вычеркивать их - это НЕ простые числа
#define PRIME 0
#define NOTPRIME 1

// Заполняет массив a значениями a[i]: является ли число i простым или нет
void fill_primes(char a[], int n)
{
    // 0 и 1 - НЕ простые числа
    a[0] = a[1] = NOTPRIME;
    
    // вычеркиваем
    for (int i = 2; i * i <= n; i++) {
        // вычеркивать кратные 6 бесполезно, их вычеркнули раньше, когда вычеркивали 2 или 3
        if (a[i] == NOTPRIME)
            continue;
        
        // вычеркиваем кратные i
        for (int j = i + i; j < n; j += i)
            a[j] = NOTPRIME;
    }
}

int main()
{
    char prime[MAX_PRIME] = {0};
    
    fill_primes(prime, MAX_PRIME);
    
    
    for (int i = 3; i < MAX_PRIME; i++)
        if (prime[i] == PRIME)
            printf("%d ", i);
    printf("\n");
    
    for (int i = 1000; i * i < MAX_PRIME; i++)
        if (prime[i] == PRIME)
            printf("%d ", i * i);
    printf("\n");
    
    
    /*
    int n, number;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &number);
        if (prime[number] == PRIME)
            printf("%d ", number);
    }
    printf("\n");
    */
    
    return 0;
}