#include <stdio.h>

int fib (int n, int depth) {
	static int count;
	count ++;
	printf("%-*c call fib(%d)\n", depth, '>', n);
	if (n == 0 || n == 1) {
		printf("%-*c f(0) = f(1) = 1\n", depth, '>');
		return 1;
	}
	int res = fib (n-1, depth+4) + fib (n-2, depth+4);
	printf("%-*c fib(%d) = %d\n", depth, '>', n, res);
	printf("count=%d\n", count);
	return res; 
}
int main() {
	int n = 4;
	n = 20;
	printf("main: fib(%d) = %d\n", n, fib(n, 1));
	return 0;
}
