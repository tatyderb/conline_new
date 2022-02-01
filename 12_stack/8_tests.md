# Стек на основе массива. Рефакторинг тестов

lesson = 308171
lang = c_valgrind

##  VIDEO

<iframe width="556" height="311" src="https://www.youtube.com/embed/zk8HoTRI4cE" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

## Что в тестах плохо?

Сначала вернем значение N 8.

Чтобы написать тесты для стека с массивом из 8 элементов сейчас нужно копировать код тестов. Такой код трудно анализировать и быстро ответить на вопрос - точно ли 8 элементов добавляются и потом удаляются.

Разумно определить те числа, что мы кладем в стек, в отдельном массиве и потом push все числа из массива.

## Сворачиваем тесты push в цикл

Тесты функции `push` станут короче и понятнее:

```cpp
Data test[N] = {5, 17, -3, 0, 1, 2, 3, 4};
Data d;
for(int i = 0; i < N; i++) {
    d = test[i];
    printf("push %d :", d);
    push(st, d);
    print(st);      // 5
    printf("empty: %s\n", is_empty(st) ? "YES" : "NO");     // NO
}
```
Еще лучше параноидально проверить, что мы будем класть именно столько чисел, сколько может вместить стек:

```cpp
    Data test[] = {5, 17, -3, 0, 1, 2, 3, 4};
    // проверили, что чисел столько, сколько размер стека
    assert(sizeof(test) == sizeof(st->a));
```

Чтобы заработала проверка `assert` нужно не забыть

```cpp
#include <assert.h>
```

## Сворачиваем тесты на pop в цикл

Аналогично сделаем тесты на pop

```cpp
    // тесты для pop
    for(int i = 0; i < N; i++) {
        d = pop(st);
        printf("pop %d :", d);
        print(st);
    }
```

Очень много приходится проверять глазами - правильно ли печатают наши тесты. Тесты, которые сами проверяют свою правильность, называются автоматическими. Подумайте, как их можно написать.

## Итого

```cpp
#include <stdio.h>
#include <assert.h>

// нужно хранить другие данные в стеке?             
// Измени тип хранимых данных в одном месте.
typedef int Data;   

#define N 8
typedef struct {
    Data a[N];      // место для данных
    unsigned int n; // сколько данных хранится
} Stack;

// печать стека
void print(Stack * st) 
{
    for(unsigned int i = 0; i < st->n; i++) 
        printf("%d ", st->a[i]);
    printf("\n");
}

// инициализация стека
void init(Stack * st) {
    st->n = 0;
}    

// добавить данные data в стек
void push(Stack * st, Data data) {
    st->a[st->n] = data;
    st->n ++;
}

// удалить данные с вершины стека, вернуть эти данные
Data pop(Stack * st) {
    return st->a[-- st->n];
}

// проверить, что стек пустой, из него нельзя ничего достать
int is_empty(Stack * st) {
    return st->n == 0;
}

// проверить, что стек полон, в него нельзя ничего положить
int is_full(Stack * st) {
    return st->n == sizeof(st->a) / sizeof(st->a[0]);
}

int main()
{
    Stack stack;            // создаем стек
    Stack * st = &stack;    // указатель на созданный стек
    
    init(st);
    printf("empty: %s\n", is_empty(st) ? "YES" : "NO"); // YES
    printf("full: %s\n", is_full(st) ? "YES" : "NO");   // NO
    print(st);              // ничего не печатается
    
    Data test[] = {5, 17, -3, 0, 1, 2, 3, 4};
    // проверили, что чисел столько, сколько размер стека
    assert(sizeof(test) == sizeof(st->a));
    
    Data d;
    // тесты для push
    for(int i = 0; i < N; i++) {
        d = test[i];
        printf("push %d :", d);
        push(st, d);
        print(st);
        printf("empty: %s\n", is_empty(st) ? "YES" : "NO"); // NO
    }
    
    printf("full: %s\n", is_full(st) ? "YES" : "NO");   // YES
    
    // тесты для pop
    for(int i = 0; i < N; i++) {
        d = pop(st);
        printf("pop %d :", d);
        print(st);      // pop -3: 5 17
    }
    printf("empty: %s\n", is_empty(st) ? "YES" : "NO"); // YES
    printf("full: %s\n", is_full(st) ? "YES" : "NO");   // NO

    return 0;
}
```
напечатает:
```cpp
empty: YES
full: NO

push 5 :5
empty: NO
push 17 :5 17
empty: NO
push -3 :5 17 -3
empty: NO
push 0 :5 17 -3 0
empty: NO
push 1 :5 17 -3 0 1
empty: NO
push 2 :5 17 -3 0 1 2
empty: NO
push 3 :5 17 -3 0 1 2 3
empty: NO
push 4 :5 17 -3 0 1 2 3 4
empty: NO
full: YES
pop 4 :5 17 -3 0 1 2 3
pop 3 :5 17 -3 0 1 2
pop 2 :5 17 -3 0 1
pop 1 :5 17 -3 0
pop 0 :5 17 -3
pop -3 :5 17
pop 17 :5
pop 5 :
empty: YES
full: NO
```

## TASKINLINE Стек на основе массива

Вы прочитали и разобрались в коде. Очень полезно после этого закрыть теорию, и повторить те же или чуть другие выкладки самим. Пока читаешь - все понятно, а как начинаешь писать сам, вылезают ошибки.

Реализуйте структуру данных "стек". Для этого при объявленной структуре

```cpp
#define N 8
typedef int Data;

typedef struct {
    Data a[N];      // место для данных
    unsigned int n; // сколько данных хранится
} Stack;

```

Реализуйте функции работы со стеком:

```cpp
void stack_init(Stack * s);
void stack_push(Stack * s, Data x);
Data stack_pop(Stack * s);
Data stack_get(Stack * s);
void stack_clear(Stack * s);
void stack_print(Stack * s);
int  stack_size(Stack * s);
int  stack_is_empty(Stack * s);
int  stack_is_full(Stack * s);
```
* `void` **stack_init** `(Stack * s);` - необходимые действия для создания и инициализации стека. (Когда мы создаем локальную переменную, то она не инициализируется 0, т.е. в поле `n` может лежать любое число.)
* `void` **stack_push** `(Stack * s, Data x);` - кладет число `х` в стек;
* `Data` **stack_pop** `(Stack * s);` - достает одно число из стека и возвращает его
* `Data` **stack_get** `(Stack * s);` - возвращает число, лежащее на верхушке стека, **не изменяя состояния стека**;
* `void` **stack_clear** `(Stack * s);` - очищает стек (функция `stack_is_empty` должна вернуть 1).
* `void` **stack_print** `(Stack * s);` - распечатывает через пробел числа, лежащие в стеке. С самого первого до верхнего. В конце переводит строку.
* `int`  **stack_size** `(Stack * s);` - возвращает количество элементов, лежащих в стеке
* `int`  **stack_is_empty** `(Stack * s);` - возвращает 1 если стек пуст, иначе возвращает 0.
* `int`  **stack_is_full** `(Stack * s);` - возвращает 1 если стек полон (в него нельзя добавлять данные, это приведет к переполнению), иначе возвращает 0.

**Посылать ТОЛЬКО реализацию требуемых функций**. main - не надо, определение структуры - не надо, прототипы функций - не надо.

**Цель задачи - приучиться разбивать задачу на этапы и отлаживать каждый этап.**

Функция для тестирования кода (рекомендуем закомментировать почти все тесты, кроме первых строк, реализовать нужные для этих тестов функции, отладить их, потом откомментировать еще код для 1-2 функций и проверить для них, пока весь тест не заработает).

```cpp
откопировать сюда после отладки задачи
```
HEADER
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define N 8
typedef int Data;
typedef struct {
    Data a[N];      // место для данных
    unsigned int n; // сколько данных хранится
} Stack;

void stack_init(Stack * s);
void stack_push(Stack * s, Data x);
Data stack_pop(Stack * s);
Data stack_get(Stack * s);
void stack_clear(Stack * s);
void stack_print(Stack * s);
int  stack_size(Stack * s);
int  stack_is_empty(Stack * s);
int  stack_is_full(Stack * s);

// тест из примера https://stepik.org/lesson/308171/step/5
void test0()
{
    Stack stack;            // создаем стек
    Stack * st = &stack;    // указатель на созданный стек

    stack_init(st);
    printf("empty: %s\n", stack_is_empty(st) ? "YES" : "NO"); // YES
    printf("full: %s\n", stack_is_full(st) ? "YES" : "NO");   // NO
    stack_print(st);              // ничего не печатается

    Data test[] = {5, 17, -3, 0, 1, 2, 3, 4};
    // проверили, что чисел столько, сколько размер стека
    assert(sizeof(test) == sizeof(st->a));
    
    Data d;
    // тесты для push
    for(int i = 0; i < N; i++) {
        d = test[i];
        printf("push %d :", d);
        stack_push(st, d);
        stack_print(st);
        printf("empty: %s\n", stack_is_empty(st) ? "YES" : "NO"); // NO
    }

    printf("full: %s\n", stack_is_full(st) ? "YES" : "NO");   // YES

    // тесты для pop
    for(int i = 0; i < N; i++) {
        d = stack_pop(st);
        printf("pop %d :", d);
        stack_print(st);      // pop -3: 5 17
    }
    printf("empty: %s\n", stack_is_empty(st) ? "YES" : "NO"); // YES
    printf("full: %s\n", stack_is_full(st) ? "YES" : "NO");   // NO
}    


int main()
{
	Stack s;
	// s.n=0;
	char str[160];
	Data x;
	while(1 == scanf("%80s", str)) {
		printf("%s\n", str);
		
		if (strcmp("end", str)==0) {
			break;
		}
		else if (strcmp("push", str)==0) {
			scanf("%d", &x);
			stack_push(&s, x);
		}
		else if (strcmp("pop", str)==0) {
			x = stack_pop(&s);
			printf("%d\n", x);
		}
		else if (strcmp("get", str)==0) {
			x = stack_get(&s);
			printf("%d\n", x);
		}
		else if (strcmp("print", str)==0) {
			stack_print(&s);
		}
		else if (strcmp("size", str)==0) {
			x = stack_size(&s);
			printf("%d\n", x);
		}
		else if (strcmp("clear", str)==0) {
			stack_clear(&s);
		}
		else if (strcmp("create", str)==0) {
			stack_init(&s);
		}
		else if (strcmp("is_empty", str)==0) {
			x = stack_is_empty(&s);
			printf("%d\n", x);
		}
		else if (strcmp("is_full", str)==0) {
			x = stack_is_empty(&s);
			printf("%d\n", x);
		}
		else if (strcmp("test0", str)==0) {
			test0();
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
empty: YES
full: NO

push 5 :5
empty: NO
push 17 :5 17
empty: NO
push -3 :5 17 -3
empty: NO
push 0 :5 17 -3 0
empty: NO
push 1 :5 17 -3 0 1
empty: NO
push 2 :5 17 -3 0 1 2
empty: NO
push 3 :5 17 -3 0 1 2 3
empty: NO
push 4 :5 17 -3 0 1 2 3 4
empty: NO
full: YES
pop 4 :5 17 -3 0 1 2 3
pop 3 :5 17 -3 0 1 2
pop 2 :5 17 -3 0 1
pop 1 :5 17 -3 0
pop 0 :5 17 -3
pop -3 :5 17
pop 17 :5
pop 5 :
empty: YES
full: NO
====
create
push 3
push 7
push 2
print
is_empty
is_full
pop
pop
pop
is_empty
is_full
----
create
push
push
push
print
3 7 2
is_empty
0
is_full
0
pop
2
pop
7
pop
3
is_empty
1
is_full
0
====


