#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int cmp_char(const void * p1, const void * p2)
{
    char x = *(const char *)p1;
    char y = *(const char *)p2;
    char res = x - y;
    int res1 = x - y;
    printf("x=%d y=%d res=%d %d\n", x, y, res, res1);
    return res;
}

int main()
{
    char a = 2, b = 7, d = 7;
    assert(cmp_char(&a, &b) < 0);    // x=2 y=7 res=5    5 < 0
    assert(cmp_char(&b, &a) > 0);    // x=7 y=2 res=-5  -5 > 0
    assert(cmp_char(&b, &d) == 0);   // x=7 y=7 res=0    0 == 0
    
    a = -128, b = -70, d = 70;
    cmp_char(&a, &b);               // x=-128 y=-70 res=-58      
    cmp_char(&a, &d);               // x=-128 y=70 res=58, т.е -128 > 70 ?
    cmp_char(&b, &d);               // x=-70 y=70 res=116, т.е -70 > 70  ?
    
    char arr[] = {-128, -70, 70};                   // уже отсортирован по возрастанию
    qsort(arr, 3, sizeof(char), cmp_char);
    printf("%d %d %d\n", arr[0], arr[1], arr[2]);   // 70 -128 -70 сломали
    
    return 0;
}