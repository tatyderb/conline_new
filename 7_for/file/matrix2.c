#include <stdio.h>

/* Суммирует количество яблок в 1 ряду яблонь */
int pikup_1row() 
{
	int x;			// яблок на одной (текущей) яблоне
	int sum; 		// уже собрали яблок
	int n;			// количество деревьев
	int i;			// сколько деревьев уже обработали
	
	scanf("%d", &n);
	
	sum = 0;		// не забыть очистить корзину перед сбором яблок!
	for(i= 0; i < n; i++) {
		scanf("%d", &x);
		sum += x;
		printf("i=%d x=%d sum=%d\n", i, x, sum);
	}
	return sum;
}
int main()
{
A:	
	int rows, j, total, n, i, x, sum;
B:	
	scanf("%d", &rows);
	total = 0;
C:	
	for (j = 0; j < rows; j++) {
D:
		scanf("%d", &n);
		sum = 0;		// не забыть очистить корзину перед сбором яблок!
E:
		for(i= 0; i < n; i++) {
F:			
			scanf("%d", &x);
			if (x < 0)
				goto M;
			sum += x;
			printf("j=%d i=%d x=%d sum=%d\n", j, i, x, sum);
G:			
		}
H:		
		total += sum;
		printf("j=%d total=%d\n", j, total);
K:		
	}	
L:	
	printf("%d\n", total);
M:	
	return 0;
}
