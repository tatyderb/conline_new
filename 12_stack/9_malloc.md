# Стек на основе динамического массива

lesson = 308172
lang = c_valgrind

##  VIDEO

<iframe width="556" height="311" src="https://www.youtube.com/embed/_JsRngeD4kA" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

## Что нужно изменить?

Стек на основе массива просто написать.

Не знаем заранее, какой размер массива нужен в задачах.

Если стек маленький, увеличим N. Если нужно много маленьких стеков, то память используется не эффективно при большом N.

Напишем стек, который сам расширяется при добавлении элементов.

Так же можно написать, чтобы он сам сужался при удалении многих элементов.

Сделаем стек на основе *динамического* массива.

## Структура стека на основе динамического массива

Так как захват памяти "тяжелая" операция, то постараемся найти баланс между эффективным использованием памяти и частотой вызова `realloc`.

Чтобы не делать на каждый push и pop `realloc`, будем, как в случае обычного массива, сразу захватывать память. Сколько уже выделено памяти запишем в поле `size`.

![Изображение структуры стека](https://stepik.org/media/attachments/lesson/308172/stack_darr.png)

```cpp
typedef int Data;
typedef struct {
    Data * a;           // указатель на динамически 
                        // выделенную память
    unsigned int n;     // сколько элементов хранится в стеке
    size_t size;        // на сколько элементов выделена память
} Stack;
```

Заметим, что `size` - это на сколько *элементов массива* (в штуках) выделена память, а не в sizeof и не в байтах.

## Изменение init

Некоторые функции не изменятся, например, `print` и `is_empty`. Посмотрим на остальные функции.

При инициализации стека теперь нужно разобраться с динамической памятью (выделить или написать так, чтобы `realloc` работал без ошибок).

Вариант 1. Сразу выделяем память в `init`:
```cpp
#define N 10

void init(Stack * st) {
    st->n = 0;
    st->size = N;
    st->a = malloc(st->size * sizeof(Data));
}
```
В этом случае можно передавать желаемый размер данных `n` еще одним аргументом функции: 

`void init(Stack * st, insigned int n);`

Вариант 2. а указывает на `NULL`:
```cpp
void init(Stack * st) {
    st->n = 0;
    st->size = 0;
    st->a = NULL;
}
```

## push

В `push` нужно дописать код, который при попытке переполнить стек выделяет дополнительную память.

Как изменится функция `is_full`?

```cpp
void push(Stack * st, Data data) {
    if (is_full(st)) {
        // изменение размера можно написать в отдельной функции 
        // set_size(st, new_size)
        st->size += N;
        st->a = realloc(st->a, st->size * sizeof(Data));
    }
    st->a[st->n] = data;
    st->n ++;
}
```

Если стек полон, сколько нужно добавить памяти? Есть разные стратегии:

* Всегда увеличивать на N элементов.
* Всегда увеличивать в 2 раза (в 1.5, на треть и тп)

Выберите, какая вам больше нравится или придумайте свою. Оцените ее плюсы и минусы.

## pop

Аналогично можно улучшить `pop`, если уменьшать динамически выделенную память, когда в стеке становится слишком мало данных.

При реализации `pop` придерживайтесь той же стратегии изменения размера памяти, что и в `push`.

## Освобождение памяти

Если запустить тесты на valgrind, то увидим диагностику об утечке памяти. Мы пишем в коде `malloc` и `realloc`, но не пишем `free`.

Напишем функцию `clear` освобождения динамической памяти.

```cpp
void clear(Stack * st) {
    free(st->a);
    st->a = NULL;
    st->size = 0;
    st->n = 0;
}    
```
Почему не обойтись одним `free`?

Во-первых, если кто-то после `clear` решит вновь добавлять данные, стек полностью готов к работе.

Во-вторых, если вызвать два раза подряд `clear`, то дважды вызванное `free` от одно и того же адреса приведет к падению программы, а `free(NULL)` будет работать корректно (ничего не делает, и не падает).

Заметим, что `clear` можно написать используя `init` (вариант 2):
```cpp
void clear(Stack * st) {
    free(st->a);
    init(st);
}    
```

## create и destroy

Если начали выделять память динамически, то стоит создание стека полностью перенести в функцию `create`:
```cpp
Stack * st = create();
```
То есть выделять память не только под динамический массив (один `malloc`), но и под саму структуру `Stack` (еще один `malloc`):

```cpp
Stack * create() {
    Stack * st = malloc(sizeof(Stack));
    init(st);
    return st;
}
```
Тогда и `destroy` должен содержать такое же количество `free`:
```cpp
Stack * destroy(Stack * st) {
    if (st != NULL) {
        free(st->a);
        free(st);
    }
    return NULL;
}
```
Внимание, сначала освобождаем память, на которую указывает `st->a`, а потом только освобождаем память `st` (в которой записано поле `a`), а не наоборот.

Не стоит сначала сносить дом, а потом искать в нем на столе любимую чашку.

Почему возвращаем `Stack *`? Такой вызов функции можно сделать больше одного раза:
```cpp
st = destroy(st);
```

Иначе:
```cpp
destroy(st);    // OK
destroy(st);    // Segmentation fault
```
"Контрольный выстрел" не всегда делает лучше.

## TASKINLINE stack_31 Стек на основе динамического массива

Повторение - мать учения. Попробуйте не подглядывая в теорию реализовать функции для работы со стеком.

Реализуйте структуру данных "стек", который бы был защищен от переполнения. Размер стека должен быть ограничен только размером доступной оперативной памяти.

```cpp
typedef int Data;

typedef struct {
    int n;
    int size;
    Data * a; 
} Stack;
```
* **a** - динамический массив, в котором храним данные стека,
* **size** - размер выделенной памяти для данных стека (т.е. размер динамического массива a в ячейках, а не байтах).
* **n** - номер первой пустой ячейки массива.

```cpp
Stack * stack_create(int size);
void stack_push(Stack * s, Data x);
Data stack_pop(Stack * s);
Data stack_get(Stack * s);
void stack_print(Stack * s);
int  stack_size(Stack * s);
int  stack_is_empty(Stack * s);
void stack_clear(Stack * s);
Stack * stack_destroy(Stack * s);
Stack * stack_create(int size);
```

* `Stack *` **stack_create** `(int size);` - необходимые действия для создания и инициализации стека размером **size** ячеек. Теперь эта функция полностью **создает и инициализирует стек**. Заметьте, что у функции изменились аргументы и тип возвращаемого значения. Гарантируется, что в тестах она будет вызвана, и вызвана единственный раз перед дальнейшей работой со стеком.
* `void` **stack_push** `(Stack * s, Data x);` - кладет число **х** в стек.
* `Data` **stack_pop** `(Stack * s);` - достает одно число из стека и возвращает его.
* `Data` **stack_get** `(Stack * s);` - возвращает число, лежащее на верхушке стека, не изменяя состояния стека.
* `int` **stack_is_empty** `(Stack * s);` - возвращает 1, если стек пуст; 0 - в противном случае.
* `void` **stack_print** `(Stack * s);`	- распечатывает через пробел числа, лежащие в стеке. С самого первого до верхнего. В конце переводит строку.
* `int` **stack_size** `(Stack * s);` - возвращает количество элементов, лежащих в стеке.
* `void` **stack_clear** `(Stack * s);` - очищает стек, не разрушая его.
* `Stack *` **stack_destroy** `(Stack * s);` - освобождает память. Всю память, занятую стеком, а не часть памяти. **Возвращает NULL**.

Посылать только реализацию функций.

Функцию main, объявление структуры и прототипы функций посылать НЕ нужно.

Пример кода (в комментариях написано что будет выведено на печать)

```cpp
void test0()
{
    Stack * sp = stack_create(3);

    printf("is_empty=%d\n", stack_is_empty(sp));    // is_empty=1
    printf("size=%d\n", stack_size(sp));            // size=0

    stack_push(sp, 5);
    stack_push(sp, 19);
    stack_push(sp, -2);
    stack_print(sp);                                // 5 19 -2

    stack_push(sp, 27);
    stack_print(sp);                                // 5 19 -2 27

    printf("is_empty=%d\n", stack_is_empty(sp));    // is_empty=0
    printf("size=%d\n", stack_size(sp));            // size=4

    x = stack_pop(sp);
    printf("x=%d\n", x);                            // x=27

    x = stack_pop(sp);
    printf("x=%d\n", x);                            // x=-2

    stack_print(sp);                                // 5 19

    while (!stack_is_empty(sp)) {
        x = stack_pop(sp);
        printf("x=%d\n", x);
        stack_print(sp);
    }
                                                    // x=19
                                                    // 5
                                                    // x=5
                                                    // пустая строка

    if (NULL == stack_destroy(sp))
        printf("end\n");                           // end
}
```
HEADER
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int Data;

typedef struct{
	int n;
	int size;
    int * a;
} Stack;

Stack * stack_create(int size);
void stack_push(Stack * s, Data x);
Data stack_pop(Stack * s);
Data stack_get(Stack * s);
void stack_print(Stack * s);
int  stack_size(Stack * s);
int  stack_is_empty(Stack * s);
void stack_clear(Stack * s);
Stack *stack_destroy(Stack * s);

void test0()
{
    Data x;
    Stack * sp = stack_create(3);

    printf("is_empty=%d\n", stack_is_empty(sp));    // is_empty=1
    printf("size=%d\n", stack_size(sp));            // size=0

    stack_push(sp, 5);
    stack_push(sp, 19);
    stack_push(sp, -2);
    stack_print(sp);                                // 5 19 -2

    stack_push(sp, 27);
    stack_print(sp);                                // 5 19 -2 27

    printf("is_empty=%d\n", stack_is_empty(sp));    // is_empty=0
    printf("size=%d\n", stack_size(sp));            // size=4

    x = stack_pop(sp);
    printf("x=%d\n", x);                            // x=27

    x = stack_pop(sp);
    printf("x=%d\n", x);                            // x=-2

    stack_print(sp);                                // 5 19

    while (!stack_is_empty(sp)) {
        x = stack_pop(sp);
        printf("x=%d\n", x);
        stack_print(sp);
    }
                                                    // x=19
                                                    // 5
                                                    // x=5
                                                    // пустая строка

    if (NULL == stack_destroy(sp))
        printf("end\n");                            // end
}

int main()
{
	Stack * ps = NULL;
	char str[180];
	Data x;
	while(1) {
		scanf("%80s", str);
		printf("%s\n", str);
		if (str[0]=='#')        // закомментаренные строки теста
			continue;
		
		if (strcmp("end", str)==0) {
			ps = stack_destroy(ps);
			break;
		}
		else if (strcmp("create", str)==0) {
			ps = stack_create(3);
		}
		else if (strcmp("push", str)==0) {
			scanf("%d", &x);
			printf("%d\n", x);
			stack_push(ps, x);
		}
		else if (strcmp("pop", str)==0) {
			x = stack_pop(ps);
			printf("%d\n", x);
		}
		else if (strcmp("print", str)==0) {
			stack_print(ps);
		}
		else if (strcmp("get", str)==0) {
			x = stack_get(ps);
			printf("%d\n", x);
		}
		else if (strcmp("is_empty", str)==0) {
			printf("%d\n",  stack_is_empty(ps));
		}
		else if (strcmp("size", str)==0) {
			x = stack_size(ps);
			printf("%d\n", x);
		}
		else if (strcmp("clear", str)==0) {
			stack_clear(ps);
		}
		else if (strcmp("test0", str)==0) {
			test0();
            return 0;   // чтобы не было дополнительных destroy при end
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
is_empty=1
size=0
5 19 -2
5 19 -2 27
is_empty=0
size=4
x=27
x=-2
5 19
x=19
5
x=5

end
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
5
print
5
push
2
print
5 2
pop 
2
print
5
end
====
create
is_empty
push 5
print
push 2
print
pop
print
is_empty
pop
print
is_empty
print
end
----
create
is_empty
1
push
5
print
5
push
2
print
5 2
pop
2
print
5
is_empty
0
pop
5
print

is_empty
1
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
is_empty
size
print
pop
print
size
clear
size
print
is_empty
end
----
create
push
1
push
2
push
3
push
4
push
5
push
6
push
7
push
8
push
9
push
10
print
1 2 3 4 5 6 7 8 9 10
push
23
is_empty
0
size
11
print
1 2 3 4 5 6 7 8 9 10 23
pop
23
print
1 2 3 4 5 6 7 8 9 10
size
10
clear
size
0
print

is_empty
1
end
====
