#include <stdio.h>

void foo1(int a[3][4])
{
    printf("%s: %zu %zu %d\n", __FUNCTION__, sizeof(a), sizeof(a[0]), a[1][2]);
}
void foo2(int a[][4])
{
    printf("%s: %zu %zu %d\n", __FUNCTION__, sizeof(a), sizeof(a[0]), a[1][2]);
}    
void foo3(int (*a)[4])
{
    printf("%s: %zu %zu %d\n", __FUNCTION__, sizeof(a), sizeof(a[0]), a[1][2]);
}
/*
void foo4(int *a[4])
{
    printf("%s: %zu %zu %d\n", __FUNCTION__, sizeof(a), sizeof(a[0]), a[1][2]);
}
*/
void foo5(int **a, int rows, int cols)
{
    printf("%s: %zu %zu %d\n", __FUNCTION__, sizeof(a), sizeof(a[0]), a[1][2]);
}    

int main()
{
    int a[3][4] = {
        {1, 2, 3, 4},
        {11, 12, 13, 14},
        {21, 22, 23, 24}
    };
    printf("int:  %zu\n", sizeof(int));
    printf("int*: %zu\n", sizeof(int*));
    printf("%s: %zu %zu %d\n", __FUNCTION__, sizeof(a), sizeof(a[0]), a[1][2]);
    foo1(a);
    foo2(a);
    foo3(a);
    // foo4(a);
    foo5(a, 3, 4);

    return 0;
}