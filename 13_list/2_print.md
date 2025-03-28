# Односвязный список - печать

lesson = 308792


##  VIDEO

Создание модели из 3 узлов и печать односвязного списка

<p>Платформа:</p>

<p><iframe allowfullscreen="" height="315" src="https://plvideo.ru/embed/PRL33grG9mxL" width="560"></iframe></p>

<p>Youtube:</p>

<p><iframe allowfullscreen="" height="315" src="https://www.youtube.com/embed/UqQ2dtJVccw" width="560"></iframe></p>

## Модель односвязного списка

![Модель списка](https://stepik.org/media/attachments/lesson/308791/list1_model.png)

Сделаем модель списка из 3 узлов a, b, c.

```cpp
int main()
{
    Node a, b, c;

    Node * list = &a;
    a.data = 3;     a.next = &b;
    b.data = 17;    b.next = &c;
    c.data = 21;    c.next = NULL;
    
    return 0;
}
```
Для удобства понимания какой указатель куда указывает, придумаем у каждого узла адрес и запишем эти адреса в поля узлов и переменные. На самом деле адреса очень длинные, но мы рисуем модель для понимания как устроена структура данных и как с ней работать.

## Печать модели

**Если вы можете сами сразу написать функцию печати, напишите ее и отладьте.** В этом случае пропустите шаги до [реализации функции print]().

Напечатаем данные, которые хранятся в списке. Это поля data узлов a, b, c.

В функцию main добавим код:
```cpp
    printf("%d ", a.data);
    printf("%d ", b.data);
    printf("%d ", c.data);
    printf("\n");
```
В функции печати не будет узлов a, b, c. Будет только переменная `list`. Избавимся от имен узлов. Перейдем к переменной `Node * p;`, которая будет указывать на узел, который будем печатать.

Сначала `p` указывает на тот же узел, что и `list`. Это узел `a`.

```cpp
Node * p = list;
```
Заменим переменную `a` на использование переменной `p`.
```cpp
    // printf("%d ", a.data);
    printf("%d ", p->data);     // 3
```
Передвинем указатель p на узел b. Посмотрим, как можно использовать адреса, которые написаны в рисунке модели. Узел b лежит по адресу 200. Значит, в переменную p нужно записать число 200. Это число в поле next узла а. На этот же узел указывает сейчас p. Значит
```cpp
    p = p->next;    // в p записали адрес 200
```
Заметим, что напечатать значение в узле b (на который сейчас указывает p) и передвинуть указатель p на узел c можно таким же кодом:
```cpp
    // printf("%d ", b.data);
    printf("%d ", p->data);     // 17
    p = p->next;    // в p записали адрес 140
```
То же для узла с.
```cpp
    // printf("%d ", c.data);
    printf("%d ", p->data);     // 21
    p = p->next;    // в p записали адрес NULL; можно не делать
```

## Свернем печать в цикл

Полученный код
```cpp
    Node * p = list;
    printf("%d ", p->data); 
    p = p->next;
    printf("%d ", p->data); 
    p = p->next;
    printf("%d ", p->data); 
    p = p->next;
    printf("\n");
```
перепишем в виде цикла:
```cpp
    for(Node * p = list; p != NULL; p = p->next)
        printf("%d ", p->data); 
    printf("\n");
```

## Отдельная функция print

Вынесем код в отдельную функцию и получим:

```cpp
#include <stdio.h>

typedef int Data;

typedef struct Node Node;
struct Node {
    Data data;
    Node * next;
};    

// печать списка
void print(Node * list) {
    for (Node * p = list; p != NULL; p = p->next) {
        printf("%d ", p->data);
    }
    printf("\n");
}

int main() {
    // model
    Node a, b, c;

    Node * list = &a;
    a.data = 3;     a.next = &b;
    b.data = 17;    b.next = &c;
    c.data = 21;    c.next = NULL;

    print(list);        // 3 17 21
    
    return 0;
}
```