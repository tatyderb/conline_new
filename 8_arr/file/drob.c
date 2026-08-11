#include <stdio.h>
#include <stdlib.h>
void print_arr(int * arr, int n)
{
    int i;
    for(i = 0; i < n; i++)
        printf("%d:%d ", i, arr[i]);
}
void print_drob(int * drob, int start_period, int stop_period)
{
    
    
    printf("0,");
    int i;
    for(i = 0; i < start_period; i++)
        printf("%d", drob[i]);
    if(stop_period == -1) {
        printf("\n");
        return;
    }
    printf("(");
    for(; i < stop_period; i++)
        printf("%d", drob[i]);
    printf(")");
}
void drob(int a, int b)
{
    int * drob = malloc(b * sizeof(int));
    int * rest = malloc(b * sizeof(int));
    int i;
    for(int i = 0; i < b;i++)
        rest[i] = -1;
    
    a = a*10;
    for(i =0; i < b; i++) {
        printf("i=%d a=%d/%d drob=> ", i, a, b);
        print_arr(drob, b);
        printf("\t rest=> ");
        print_arr(rest, b);
        printf("\n");
        
        if(a == 0) {        // периода нет
            print_drob(drob, i, -1);
            break;
        }
        if(rest[a%b] != -1) { // нашли период
            print_drob(drob, rest[a%b], i);
            break;
        }
        rest[a%b] = i;
        drob[i] = a/b;
        a = (a%b)*10;
    }
    free(rest);
    free(drob);
}
int main()
{
    int a, b;
    scanf("%d%d", &a, &b);
    drob(a, b);
    return 0;
}
        