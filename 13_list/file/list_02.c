#ifdef AAA

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int Data;
struct Node {
    Data val;
    struct Node * next;
};

struct Node * list_create();
void list_push(struct Node ** list, Data x);
Data list_pop(struct Node ** list);
Data list_get(struct Node * list);
void list_print(struct Node * list);
int  list_size(struct Node * list);
void list_clear(struct Node ** s);
int  list_is_empty(struct Node * list);

void test0()
{
    struct Node * list = list_create();
    list_print(list);                               // пустая строка
    printf("is_empty = %d\n", list_is_empty(list)); // is_empty = 1
    printf("size = %d\n", list_size(list));         // size = 0

    list_push(&list, 21);
    list_print(list);                               // 21
    list_push(&list, 17);
    list_print(list);                               // 17 21
    list_push(&list, 3);
    list_print(list);                               // 3 17 21
    printf("is_empty = %d\n", list_is_empty(list)); // is_empty = 0
    printf("size = %d\n", list_size(list));         // size = 3
    
    Data x = list_pop(&list);
    printf("pop %d\n", x);                          // pop 3
    list_print(list);                               // 17 21
    printf("size = %d\n", list_size(list));         // size = 2

    list_clear(&list);
    list_print(list);                               // пустая строка
    printf("is_empty = %d\n", list_is_empty(list)); // is_empty = 1
    printf("size = %d\n", list_size(list));         // size = 0
}


void test()
// task example
{
	// return;
	struct Node * list = list_create();
	list_push(&list, 5);
	list_print(list);
	// 5
	list_push(&list, 72);
	list_print(list);
	// 72 5
	list_push(&list, 19);
	list_print(list);
	// 19 72 5
	
	Data x = list_size(list);
	printf("size = %d\n", x);
	// size = 3
	
	x = list_pop(&list);
	printf("x = %d\n", x);
	// x = 19
	list_print(list);
	// 72 5

	x = list_pop(&list);
	printf("x = %d\n", x);
	// x = 72
	list_print(list);
	// 5

	x = list_pop(&list);
	printf("x = %d\n", x);
	// x = 5
	list_print(list);
	// Empty list

	list_clear(&list);
	
	printf("test OK\n");
}

int main()
{
	// test();
	// return 0;
	
	struct Node * s = NULL;
	char str[81];
	Data x;
	while(1) {
		scanf("%80s", str);
		printf("%s\n", str);
		
		if (strcmp("test", str)==0) {
			test();
            return 0;
		}
		else if (strcmp("test0", str)==0) {
			test0();
            return 0;
		}
		else if (strcmp("end", str)==0) {
			list_clear(&s);
			return 0;
		}
		else if (strcmp("push", str)==0) {
			scanf("%d", &x);
			list_push(&s, x);
		}
		else if (strcmp("pop", str)==0) {
			x = list_pop(&s);
			printf("%d\n", x);
		}
		else if (strcmp("get", str)==0) {
			x = list_get(s);
			printf("%d\n", x);
		}
		else if (strcmp("print", str)==0) {
			list_print(s);
		}
		else if (strcmp("size", str)==0) {
			x = list_size(s);
			printf("%d\n", x);
		}
		else if (strcmp("create", str)==0) {
			s = list_create();
		}
		else if (strcmp("check", str)==0) {
			printf("is_empty=%d\n", list_is_empty(s));
		}
		else {
			fprintf(stderr, "Wrong test (%s)\n", str);
			return 1;
		}
	}
	
	return 0;
}

#line 10000
#endif

struct Node * list_create()
{
    return NULL;
}
void list_push(struct Node ** plist, Data x)
{
    struct Node * t = malloc(sizeof(struct Node));
    t->val = x;
    t->next = *plist;
    *plist = t;
}
Data list_pop(struct Node ** plist){
    struct Node * t = *plist;
    Data x = t->val;
    *plist = t->next;
    free(t);
    return x;
}
Data list_get(struct Node * list){
    return list->val;
}
void list_print(struct Node * list){
    struct Node * t;
    for (t=list; t!=NULL; t = t->next)
        printf("%d ", t->val);
    printf("\n");
}
int  list_size(struct Node * list)
{
    struct Node * t;
    int size = 0;
    for (t=list; t!=NULL; t = t->next)
        size ++;
    return size;
}
void list_clear(struct Node ** plist)
{
    struct Node * t;
    while (*plist!=NULL) {
        t = *plist;
        *plist = (*plist)->next;
        free(t);
    }
}
int list_is_empty(struct Node * list)
{
    return list == NULL;
}
