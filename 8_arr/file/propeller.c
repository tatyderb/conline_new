#include <stdio.h>

int main() {
	int i;
	for (i = 0; ; i = (i + 1) % 4)
		printf("\b%c", "|/-\\"[i]);
	return 0;
}