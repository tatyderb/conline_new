#include <stdio.h>

int main()
{
	int x;			// яблок на одной (текущей) яблоне
	int sum; 		// уже собрали яблок
	int n;			// количество деревьев
	int i;			// сколько деревьев уже обработали
	
	scanf("%d", &n);
	
	sum = 0;		// не забыть очистить корзину перед сбором яблок!
	for(i= 0; i < n; i++) {
		scanf("%d", &x);
		if (x < 0) {
			printf("ВОРОНЫ!\n");
			break;
		}
		sum += x;
		printf("apple tree %d: x is %d and sum is %d\n", i, x, sum);
	}
	
	printf("%d\n", sum);
	return 0;
}
