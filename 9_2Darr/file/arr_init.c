#include <stdio.h>
#include <string.h>

void print2d(int rows, int cols, int a[][cols])
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }
}
int main()
{
    int n;
    scanf("%d", &n);
    int b[n];
    int a[n][n+1];
    
    memset(b, 1, sizeof(b));
    memset(a, 1, sizeof(a));
    
    a[2][3] = 7;
    
    print2d(n, n+1, a);
    
    printf("a[0][0]=%d\n", a[0][0]);
    printf("b[0]=%d\n", b[0]);
    printf("int=%zu b=%zu\n", sizeof(int), sizeof(b));
    
    return 0;
}