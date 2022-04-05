# Задача - стек на основе односвязного списка

lesson = 659476
lang = c_valgrind

## Какую задачу делать

Делаете одну задачу из двух, или list_01, или list_02.

Это идентичные задачи, но немного разное API. Выбирайте, что вам больше нравится.

Если вы решили неверно, а ваше решение прошло, придумайте тест и напишите его в комментариях к задаче. Каждый год мы изумляемся фантазии студентов и дополняем тесты, которые бы выявляли ошибочные решения.

## TASKINLINE list_01 Стек на основе односвязного списка, тип `List`

Реализуйте структуру данных "односвязный список". Для этого при объявленных структурах `Node` (один элемент списка) и `List` (сам список)

![односвязный список](https://stepik.org/media/attachments/lesson/308791/list1.png)

```cpp
typedef int Data;
struct Node {
    Data val;               // данные, которые хранятся в одном элементе
    struct Node * next;     // указатель на следующий элемент списка
};
typedef struct Node * List;
```

* в последнем элементе списка поле `next` указывает на `NULL`.
* `List list = NULL;` если список пуст.

Реализуйте функции работы со списком:

* `List` **list_create** `();` - необходимые действия для создания и инициализации списка (просто вернуть `NULL`).
* `void` **list_push** `(List * plist, Data x);` -	кладет число х первым элементом списка.
* `Data` **list_pop** `(List * plist);` - достает первое число из списка и возвращает его.
* `Data` **list_get** `(List list);` - возвращает число, лежащее в первом узле, не изменяя состояния списка.
* `void` **list_print** `(List list);` - распечатывает через пробел числа, лежащие в списке. С самого первого до последнего. В конце переводит строку. Полезна для отладки прочих функций.
* `int` **list_size** `(List list);` - возвращает количество элементов, лежащих в списке.
* `int` **list_is_empty** `(List list);` - возвращает 1, если список пустой; иначе возвращает 0.
* `void` **list_clear** `(List * plist);` - опустошает список, освобождая память. После этого можно опять добавлять элементы в список.

```cpp
List list_create (); 
void list_push (List * plist, Data x); 
Data list_pop (List * plist); 	
Data list_get(List list); 
void list_print (List list); 
int list_size(List list); 
int  list_is_empty(List list);
void list_clear(List * plist);
```

Посылать только реализацию требуемых функций. Объявление структур и функцию `main` посылать не надо.

Пример тестирования списка:
```cpp
void test0()
{
    List list = list_create();
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
```

HEADER
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int Data;
struct Node {
    Data val;
    struct Node * next;
};
typedef struct Node * List;

List list_create();
void list_push(List * list, Data x);
Data list_pop(List * list);
Data list_get(List list);
void list_print(List list);
int  list_size(List list);
void list_clear(List * s);
int  list_is_empty(List list);

void test0()
{
    List list = list_create();
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
	List list = list_create();
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
	
	List s = NULL;
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
TEST
test0
----
test0

is_empty = 1
size = 0
21
17 21
3 17 21
is_empty = 0
size = 3
pop 3
17 21
size = 2

is_empty = 1
size = 0
====
test
----
test
5
72 5
19 72 5
size = 3
x = 19
72 5
x = 72
5
x = 5

test OK
====
create
push 5
print
push 2
print
pop
print
end
----
create
push
print
5
push
print
2 5
pop
2
print
5
end
====
create
check
push 5
print
push 2
print
pop
print
check
pop
print
check
print
end
----
create
check
is_empty=1
push
print
5
push
print
2 5
pop
2
print
5
check
is_empty=0
pop
5
print

check
is_empty=1
print

end
====
create
push 1
push 2
push 3
push 4
push 5
push 6
push 7
push 8
push 9
push 10
print
push 23
check
print
pop
print
check
end
----
create
push
push
push
push
push
push
push
push
push
push
print
10 9 8 7 6 5 4 3 2 1
push
check
is_empty=0
print
23 10 9 8 7 6 5 4 3 2 1
pop
23
print
10 9 8 7 6 5 4 3 2 1
check
is_empty=0
end
====


## TASKINLINE list_02 Стек на основе односвязного списка, тип `struct Node *`

Реализуйте структуру данных "односвязный список". Для этого при объявленных структурах `Node` (один элемент списка)

![односвязный список](https://stepik.org/media/attachments/lesson/308791/list1.png)

```cpp
typedef int Data;
struct Node {
    Data val;               // данные, которые хранятся в одном элементе
    struct Node * next;     // указатель на следующий элемент списка
};
```

* в последнем элементе списка поле `next` указывает на `NULL`.
* `struct Node * list = NULL;` если список пуст.

Реализуйте функции работы со списком:

* `struct Node *` **list_create** `();` - необходимые действия для создания и инициализации списка (просто вернуть `NULL`).
* `void` **list_push** `(struct Node ** plist, Data x);` -	кладет число х первым элементом списка.
* `Data` **list_pop** `(struct Node ** plist);` - достает первое число из списка и возвращает его.
* `Data` **list_get** `(struct Node * list);` - возвращает число, лежащее в первом узле, не изменяя состояния списка.
* `void` **list_print** `(struct Node * list);` - распечатывает через пробел числа, лежащие в списке. С самого первого до последнего. В конце переводит строку. Полезна для отладки прочих функций.
* `int` **list_size** `(struct Node * list);` - возвращает количество элементов, лежащих в списке.
* `int` **list_is_empty** `(struct Node * list);` - возвращает 1, если список пустой; иначе возвращает 0.
* `void` **list_clear** `(struct Node ** plist);` - опустошает список, освобождая память. После этого можно опять добавлять элементы в список.

```cpp
struct Node * list_create (); 
void list_push (struct Node ** plist, Data x); 
Data list_pop (struct Node ** plist); 	
Data list_get(struct Node * list); 
void list_print (struct Node * list); 
int list_size(struct Node * list); 
void list_clear(struct Node ** plist);
```

Посылать только реализацию требуемых функций. Объявление структур и функцию `main` посылать не надо.

Пример тестирования списка:
```cpp
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
```

HEADER
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
TEST
test0
----
test0

is_empty = 1
size = 0
21
17 21
3 17 21
is_empty = 0
size = 3
pop 3
17 21
size = 2

is_empty = 1
size = 0
====
test
----
test
5
72 5
19 72 5
size = 3
x = 19
72 5
x = 72
5
x = 5

test OK
====
create
push 5
print
push 2
print
pop
print
end
----
create
push
print
5
push
print
2 5
pop
2
print
5
end
====
create
check
push 5
print
push 2
print
pop
print
check
pop
print
check
print
end
----
create
check
is_empty=1
push
print
5
push
print
2 5
pop
2
print
5
check
is_empty=0
pop
5
print

check
is_empty=1
print

end
====
create
push 1
push 2
push 3
push 4
push 5
push 6
push 7
push 8
push 9
push 10
print
push 23
check
print
pop
print
check
end
----
create
push
push
push
push
push
push
push
push
push
push
print
10 9 8 7 6 5 4 3 2 1
push
check
is_empty=0
print
23 10 9 8 7 6 5 4 3 2 1
pop
23
print
10 9 8 7 6 5 4 3 2 1
check
is_empty=0
end
====

## Как лучше?

Есть ли разница, использовать `struct Node *` или `List`?

Только учебные программы пишут в стиле "сдал и забыл" (поэтому мы не любим олимпиадное программирование). В этом курсе вы видели много задач, которые постепенно развивают код. Курсовая работа будет полностью посвящена постепенному написанию большой программы в развитии.

Подумайте, если нужно будет перейти к структуре данных, где размер списка возвращался не за O(n), а за O(1) и для этого решили хранить структуру из поля указатель на начало списка и размер списка:

```cpp
struct Head {
    struct Node * list;
    int size;
};   
```

Из какой реализации проще перейти к такой реализации списка?