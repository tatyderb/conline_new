# Стек на основе массива

lesson = 308169

##  VIDEO

<iframe width="556" height="311" src="https://www.youtube.com/embed/jyJTthnEFBI" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

## Тесты для push

Напишем сначала тесты для `push`. В комментариях к коду напишем, что должно быть напечатано.

```cpp
Stack stack;            // создаем стек
Stack * st = &stack;    // указатель на созданный стек

init(st);
print(st);              // ничего не печатается

push(st, 5);
print(st);      // 5
push(st, 17);
print(st);      // 5 17
push(st, -3);
print(st);      // 5 17 -3
```

## Реализация push

После этого напишем по вызову функции `push(st, -3)` ее прототип:

```cpp
void push(Stack * st, Data data);
```

Кладем данные на первое пустое место, увеличиваем счетчик хранящихся данных.

```cpp
void push(Stack * st, Data data) {
    st->a[st->n] = data;
    st->n ++;
}
```

Компилируем, запускаем, убеждаемся, что тесты проходят верно. Запускаем с valgrind. Убеждаемся, что ошибок нет.

## pop тесты

Сначала напишем тесты. В стеке числа 5, 17, -3. Достанем их по одному, напишем в комментариях что ожидаем на печати:
```cpp
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
```

Для полноты хорошо бы протестировать еще добавление данных после удаления. Напишите эти тесты сами.

## pop реализация

По вызову функции `d = pop(st);` напишем прототип функции
```cpp
Data pop(Stack * st);
```
и реализацию. Так как нужно вернуть данные, объявим переменную `res` того же типа, что и возвращаемое значение. В конце ее вернем.

В функции нужно вычислить значение верхушки стека, и уменьшить счетчик хранимых данных (этого достаточно для "удаления" элемента из стека).

```cpp
Data pop(Stack * st) {
    Data res = st->a[st->n - 1];
    st->n --;
    return res;
}
```
еще читабельнее:
```cpp
Data pop(Stack * st) {
    st->n --;
    Data res = st->a[st->n];
    return res;
}
```
и еще короче:
```cpp
Data pop(Stack * st) {
    return st->a[-- st->n];
}
```

## Итого

```cpp
#include <stdio.h>

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

int main()
{
    Stack stack;            // создаем стек
    Stack * st = &stack;    // указатель на созданный стек
    
    init(st);
    print(st);              // ничего не печатается
    
    // тесты для push
    push(st, 5);
    print(st);      // 5
    push(st, 17);
    print(st);      // 5 17
    push(st, -3);
    print(st);      // 5 17 -3
    
    
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
    
    return 0;
}
```
Результат запуска:
```cpp

5
5 17
5 17 -3
pop -3: 5 17
pop 17: 5
pop 5:
```



