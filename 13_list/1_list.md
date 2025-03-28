# Односвязный список

lesson = 308791

##  VIDEO часть 1 односвязный список

Все видео одним эпизодом:

<iframe width="560" height="315" src="https://www.youtube.com/embed/AeOCWekAOyo" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

[Презентация](https://stepik.org/media/attachments/lesson/308791/c2019_12_169.pdf)


##  VIDEO

Определение односвязного списка

<p>Платформа:</p>

<p><iframe allowfullscreen="" height="315" src="https://plvideo.ru/embed/jA222XEnCoQt" width="560"></iframe></p>

<p>Youtube:</p>


<p><iframe allowfullscreen="" height="315" src="https://www.youtube.com/embed/TCgM8GTso3k" width="560"></iframe></p>



## Структура данных список

Односвязный список - это набор одинаковых узлов. В каждом узле хранятся данные и указатель на следующий узел.

Последний узел указывает на NULL.

![Односвязный список](https://stepik.org/media/attachments/lesson/308791/list1.png)

На основе односвязного стека можно реализовать стек.

push - добавить элемент. Новый узел указывает на бывшую вершину стека, list указывает на новый узел.

pop - list указывает на следующий за вершиной узел.

![push](https://stepik.org/media/attachments/lesson/308791/list_push.png)

## Структура узла, создание списка

Определим данные, описывающие 1 узел. 

Как в предыдущей теме, будем класть в список целые числа. Чтобы легко было перейти к другому типу данных:
```cpp
typedef int Data;
```

Определим тип для 1 узла:
```cpp
struct Node {
    Data data;
    struct Node * next;
};
typedef struct Node Node;
```

Определим пустой список. Узлов нет, list сразу указывает на NULL.
```cpp
Node * list = NULL;
```

В определении структуры можно сначала определить typedef:
```cpp
typedef struct Node Node;   // можно вместо struct Node
                            // использовать Node
struct Node {               // определяем struct Node
    Data data;
    Node * next;            // можно написать struct Node
};    
```
или сразу определить и структуру, и typedef:
```cpp
typedef struct Node {
    Data data;
    struct Node * next; // только struct Node, o Node еще неизвестно
} Node;
```

## API стека, push

![push](https://stepik.org/media/attachments/lesson/308791/list_push.png)

Как передавать list в функции push и pop?

Вспомним функцию, которая увеличивала значение переменной х на 1. Можно было написать 2 варианта:
```cpp
// x = foo1(x);         вариант 1
int foo1(int x) {
    return x + 1;
}
// foo2(&x);            вариант 2
void foo2(int * px) {
    *px = *px + 1;  // (*px)++;
}
```

Аналогично push и pop изменяют значение в переменной list. Поэтому push должен или возвращать новое значение list, или принимать указатель на list.

Вариант 1. Возвращает новый указатель на первый узел:
```cpp
// прототип
Node * push(Node * list, Data d);
Node * pop(Node * list, Data * d);  // Data * d - сюда записываем результат

// использование, должно работать и с пустым списком:
Node * list = NULL;
list = push(list, 7);

Data x;
list = pop(list, &x);   // хотим вернуть и новый list, и х
```
В `pop` тогда нужно вернуть и новый указатель на первый узел, и значение, которое достали из списка. Вернуть можно что-то одно, на второе передадим указатель и заполним значение х.

Вариант 2. Передает указатель на переменную list. Так как `list` типа `Node *`, то указатель на нее типа `Node **` и назовем эту переменную `plist`.
```cpp
// прототип
void push(Node ** plist, Data d);
Data pop(Node ** plist);     // возвращаем Data

// использование, должно работать и с пустым списком:
Node * list = NULL;
push(&list, 7);
Data x;
x = pop(&list);
```
Этот вариант будет реализован в курсе.

Можно пойти дальше и определить тип `List` как `Node *`:
```cpp
typedef Node * List;
// прототип
void push(List * plist, Data d);
Data pop(List * plist);     // возвращаем Data

// использование, должно работать и с пустым списком:
List list = NULL;
push(&list, 7);
Data x;
x = pop(&list);
```
