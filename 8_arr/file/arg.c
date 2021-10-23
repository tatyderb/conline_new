#include <stdio.h>

void foo10(int a[10]) {
	printf("foo10: %zu\n", sizeof(a));
	a = a + 1;
	printf("foo10: %p\n", a);
}
void foo(int a[]) {
	printf("foo  : %zu\n", sizeof(a));
	a = a + 1;
	printf("foo: %p\n", a);
}
void foop(int * a) {
	printf("foop : %zu\n", sizeof(a));
	a = a + 1;
	printf("foop: %p\n", a);
}
int main() {
	int a[10];
	printf("main : %zu\n", sizeof(a));
	printf("int* : %zu\n", sizeof(int*));
	printf("main: %p\n", a);
	foo10(a);
	foo(a);
	foop(a);
	return 0;
}