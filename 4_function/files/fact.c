#include <stdio.h>

int fact (int n, int depth) {
	printf("%-*c call fact(%d)\n", depth, '>', n);
	if (n == 0) {
		printf("%-*c 0! = 1\n", depth, '>');
		return 1;
	}
	int res = n * fact (n-1, depth+2);
	printf("%-*c %d! = %d\n", depth, '>', n, res);
	return res; 
}
int main() {
	printf("main: 4! = %d\n", fact(4, 1));
	return 0;
}
