#include <stdio.h>

int main()
{
    int x,  // текущий рыцарь или лжец
        n,  // всего людей в круге
        i,  // номер текущего человека в круге
        zero = 0;

    scanf("%d", &n);
    for(i = 0; i < n; i++){
        scanf("%d", &x);
        if (x == 0)
            zero ++;
    }
    printf("%d\n", zero < n-zero ? zero : n-zero);
    
    return 0;
}