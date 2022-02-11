# Двусвязный список. foreach

lesson = 308802


##  VIDEO

<p><iframe allowfullscreen="" height="315" src="https://www.youtube.com/embed/-kteSgR-x6s" width="560"></iframe></p>

## Функция foreach

Об этой функции обычно не рассказывают, а она 

* удобная
* есть в реализации списков во многих языках программирования
* полезно рассмотреть ее устройство и как решаются проблемы передачи аргументов и возвращения результата

**foreach** - функция, которая применяет переданную в аргументах функцию к каждому элементу списка.

## Как использовать?

Рассмотрим уже написанную функцию печати списка:

```cpp
void print(Node * list) {
    for (Node * p = list->next; p != list; p = p->next) {   
    // перебор элементов списка
        printf("%d ", p->data);     // обработка поля data элемента
    }
    printf("\n");                   // прочее
}
```
Распишем печать всего списка через функцию печати 1 узла, примененную ко всем элементам:
```cpp
void print_node(Data d) {
    printf("%d ", d);
}
void print(Node * list) {
    foreach(list, print_node);      // использование foreach
    printf("\n");                   // прочее
}
```
Что должна делать foreach? Перебрать все элементы и применить функцию func к каждому элементу.

```cpp
void foreach(Node * list, void (*func)(void)) {
    for (Node * p = list->next; p != list; p = p->next) {   
    // перебор элементов списка
        func(p->data);     // обработка поля data элемента
    }
}
```

## Передача аргументов в функцию func

Предположим, что мы хотим указывать в функции печати, куда именно печатать

```cpp
void print(Node * list, FILE * stream) {
    for (Node * p = list->next; p != list; p = p->next) {   
    // перебор элементов списка
        fprintf(stream, "%d ", p->data); // обработка поля data элемента
    }
    printf("\n");                   // прочее
}
```
Как видно, функция печати 1 элемента должна принимать не только поле data этого элемента, но и указатель на поток.

Мы уже видели в функции qsort, что когда не знаем какого типа может быть аргумент, мы передаем его как `void *` и в функции приводим к нужному типу.

```cpp
void print_node(Data d, void * stream) {
    fprintf((FILE*)stream, "%d ", d);
}
void print(Node * list) {
    foreach(list, print_node, stderr);      // использование foreach
    printf("\n");                   // прочее
}
```

Для такого использования нужно изменить foreach:
```cpp
void foreach(Node * list, void (*func)(void *), void * arg) {
    for (Node * p = list->next; p != list; p = p->next) {   
    // перебор элементов списка
        func(p->data, arg);     // обработка поля data элемента
    }
}
```

## Суммирование всех чисел списка через foreach

Напишем функцию, которая суммирует все элементы списка:
```cpp
Data sum_all(Node * list) {
    Data res = 0;
    for (Node * p = list->next; p != list; p = p->next) {   
        res += p->data;     // это будет функция sum_node
    }
    return res;
}
```
Перепишем ее через использование foreach.

В функцию sum_node нужно передать поле data и указатель на переменную res, чтобы можно было добавлять в нее поле data:
```cpp
void sum_node(Data d, void * vres) {
    // напоминает функцию compare, которую мы передавали в qsort
    Data * res = (Data *) vres;     
    *res = *res + d;
}
Data sum_all(Node * list) {
    Data res = 0;
    foreach(list, sum_node, &res);      // использование foreach
    return res;
}
```
