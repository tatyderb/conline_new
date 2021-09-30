#ifdef AAA
#include <stdio.h>

long long int ipow(long long int a, unsigned int n, unsigned int * depth);

int main()
{
    long long int a;
    unsigned int n, depth;
    
    scanf("%lld%u", &a, &n);
    
    long long res = ipow(a, n, &depth);
    
    printf("%lld %u\n", res, depth);
    
    return 0;
}
#endif

long long int ipow(long long int a, unsigned int n, unsigned int * depth)
{
    if (n == 0) {
        *depth = 1;
        return 1;
    }
    if (n == 1) {
        *depth = 1;
        return a;
    }
    
    long long int res;
    if (n % 2 == 0) {
        res = ipow(a, n/2, depth);
        *depth += 1;    // в обоих случаях глубина вызова +1
        return res*res;
    } else {
        res = a*ipow(a, n-1, depth);
        *depth += 1;    // в обоих случаях глубина вызова +1
        return res;
    }       
}

