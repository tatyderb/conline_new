# Стек (итого)

lesson = 308852

##  VIDEO Часть 1 (теория)

Все видео одним эпизодом:

<iframe width="560" height="315" src="https://www.youtube.com/embed/settbIgrmeM" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>
##  VIDEO Часть 2 (реализация)

Все видео одним эпизодом:

<iframe width="560" height="315" src="https://www.youtube.com/embed/Z9uJsF9xXz8" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

## Структура данных стек

* **Стек - последний пришел, первый вышел**. Стопка тарелок, пирамидка.

* **push** - добавить элемент в стек.

* **pop** - извлечь элемент из стека

## Разные варианты стеков

Стек на основе массива (не расширяем, не сужаем)

![Изображение структуры стека](https://stepik.org/media/attachments/lesson/308168/stack_arr.png)

Стек на основе динамического массива:

![Изображение структуры стека](
https://stepik.org/media/attachments/lesson/308172/stack_darr.png)

Стек на основе динамического массива единой областью памяти:
![Изображение структуры стека](
https://stepik.org/media/attachments/lesson/308173/stack_1malloc.png)

## Реализация стека на основе массива

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