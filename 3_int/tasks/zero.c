#include <stdio.h>

int main()
{
    int a = 3.5;
    int x, y;
    scanf("%d%d", &x, &y);
    
    //printf("%d/%d = %d\n", x, y, x/y);
    printf("%f/%f = %f\n", (double)x, (double)y, (double)x/y);
    printf("a=%d\n", a);
    
    return 0;
}
    