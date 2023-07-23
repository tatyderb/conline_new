# Стек на основе массива. is_empty, is_full

lesson = 308170

##  VIDEO

<iframe width="556" height="311" src="https://www.youtube.com/embed/I2CD9UBn6is" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

## Тесты для is_empty

Функции push и pop не должны проверять, можно ли их вызывать. Это задача тех, кто их вызывает. Для проверок в API обеспечим функции `is_empty` (из стека нельзя доставать) и `is_full` (в стек нельзя класть).

Напишем тесты для функции, которая проверяет пустой стек или нет. Функция `is_empty` должна возвращать истину, если стек пустой, иначе возвращать ложь.

```cpp
    printf("empty: %s\n", is_empty(st) ? "YES" : "NO");     // YES
```

Вставим этот тест сразу после создания (YES), после добавления каждого элемента и после удаления (NO). Только после удаления всех элементов тест должен опять напечатать YES.

## Реализация is_empty

После этого напишем по вызову функции `is_empty(st)` ее прототип:

```cpp
int is_empty(Stack * st);
```

Реализация простая - нужно проверить, что счетчик данных 0.

```cpp
int is_empty(Stack * st) {
    return st->n == 0;
}
```

Не забываем запускать тесты после каждой реализованной функции.

## is_full тесты

Напишем тесты аналогично тестам на `is_empty`.

```cpp
printf("full: %s\n", is_full(st) ? "YES" : "NO");
```

Тесты напечатают YES только если заполнить весь массив. Можно добавить тестов на push. А можно изменить начальный размер массива, протестировать `is_full` и откатить изменения.

Это не очень хорошо, потому что мы можем забыть откатить изменения. Еще при этом не получится прогонять все тесты при добавлении новых функций (это называется регрессионное тестирование, мы дописывая новый код можем сломать старый).

## is_full реализация

В стек нельзя положить, когда счетчик хранящихся данных равен размеру стека.

Можно написать так:
```cpp
int is_full(Stack * st) {
    return st->n == N;
}
```
но лучше вспомнить, как вычислить размер массива с помощью `sizeof`:
```cpp
int is_full(Stack * st) {
    return st->n == sizeof(st->a) / sizeof(st->a[0]);
}
```

## Итого

```cpp
#include <stdio.h>

// нужно хранить другие данные в стеке?
// Измени тип хранимых данных в одном месте.
typedef int Data;

#define N 3
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

    // тесты для push
    push(st, 5);
    print(st);      // 5
    push(st, 17);
    print(st);      // 5 17
    push(st, -3);
    print(st);      // 5 17 -3

    printf("empty: %s\n", is_empty(st) ? "YES" : "NO"); // NO
    printf("full: %s\n", is_full(st) ? "YES" : "NO");   // YES

    // тесты для pop
    Data d;
    d = pop(st);    // pop -3: 5 17
    printf("pop %d: ", d);
    print(st);

    d = pop(st);    // pop 17: 5
    printf("pop %d: ", d);
    print(st);

    d = pop(st);    // pop 5:
    printf("pop %d: ", d);
    print(st);

    printf("empty: %s\n", is_empty(st) ? "YES" : "NO"); // YES
    printf("full: %s\n", is_full(st) ? "YES" : "NO");   // NO

    return 0;
}
```
Результат запуска:
```cpp
empty: YES
full: NO

5
5 17
5 17 -3
empty: NO
full: YES
pop -3: 5 17
pop 17: 5
pop 5:
empty: YES
full: NO
```