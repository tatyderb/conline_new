#include <stdio.h>
#include <stdlib.h>

int main() {
    int a[5];
    
    a[0] = 17;
    printf("%d\n", a[0]);   // ok
    printf("%d\n", a[1]);   // uninitialized value
    
    printf("%d\n", a[5]);   // out of bounds
    printf("%d\n", a[-1]);  // out of bounds
    
    return 0;
}
