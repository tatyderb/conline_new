# Бинарное дерево поиска. Печать.

lesson = 311537


##  VIDEO

<p>Платформа:</p>

<p><iframe allowfullscreen="" height="315" src="https://plvideo.ru/embed/71DstQX0Csk0" width="560"></iframe></p>

<p>Youtube:</p>
<p>Пока ссылка на полное видео</a>

<p><iframe allowfullscreen="" height="315" src="https://www.youtube.com/embed/FKCToOPxhEg" width="560"></iframe></p>

## Модель дерева

Для построения модели дерева создадим узлы с данными, как на рисунке. Называть узлы будем не a, b, c (запутаемся), а one, two, three и так далее.

```cpp
struct Node {
    Data data;      // данные в узле
    Node * left;    // указатель на левого ребенка
    Node * right;   // указатель на правого ребенка
};
Node 
    one =   {1, NULL, NULL}, 
    two =   {2, NULL, NULL},
    three = {3, NULL, NULL},
    four =  {4, NULL, NULL},
    five =  {5, NULL, NULL},
    six =   {6, NULL, NULL},
    seven = {7, NULL, NULL},
    eight = {8, NULL, NULL},
    nine =  {9, NULL, NULL};
```

## Функция печати

Напишем функцию печати. Сначала - для пустого дерева.

```cpp
struct Node {
    Data data;      // данные в узле
    Node * left;    // указатель на левого ребенка
    Node * right;   // указатель на правого ребенка
};
void tree_print(Node * tree) {
    // тут нужно написать код
}
int main () {
    Node * tree = NULL;     // пустое дерево
    tree_print(tree);       // ничего не должно печатать
    return 0;
}
```
Очевидно, что должна быть проверка: если дерево пустое, ничего делать не нужно. Так и напишем.
```cpp
void tree_print(Node * tree) {
    // пустое дерево
    if (tree == NULL)
        return;                 // ничего не делаем, уходим
}
```
Проверьте, что это работает.

## Печать данных

Добавим в модель единственный корень 7. Очевидно, что 7 нужно напечатать.

```cpp
int main () {
    Node * tree = &seven;       // дерево из единственного узла 7
    tree_print(tree);           // 7
    return 0;
}
void tree_print(Node * tree) {
    // пустое дерево
    if (tree == NULL)
        return;                 // ничего не делаем, уходим
    // если дошли сюда, дерево НЕ пустое
    printf("%d ", tree->data);  // печатаем 7
}
```

## Печать детей

Добавим к корню 7 детей 3 и 9. Печатать должно 3 7 9.

Значит, сначала печатаем левого ребенка 3, потом данные в узле 7, потом правого ребенка 9.

```cpp
int main () {
    // строим модель
    Node * tree = &seven;
    seven.left = &three;    
    seven.right = &nine;
    
    tree_print(tree);           // 3 7 9
    return 0;
}

void tree_print(Node * tree) {

    // пустое дерево
    if (tree == NULL)
        return;                 // ничего не делаем, уходим

    // если дошли сюда, дерево НЕ пустое
    tree_print(tree->left);     // данные левого узла
    printf("%d ", tree->data);  // печатаем 7
    tree_print(tree->right);    // данные правого узла
}
```

## Полная модель

Посмотрим на дерево, в которое добавлены все узлы.

![Бинарное дерево поиска](https://stepik.org/media/attachments/lesson/311164/btree.png)

При печати узла 7, нужно сначала напечатать все числа меньшие 7. То есть все левое поддерево. Пусть левый ребенок 3 сам это сделает, без участия узла 7.

После 7 нужно напечатать числа большие 7, то есть правое поддерево. Пусть это сделает правый ребенок.

```cpp
int main () {
    // строим модель
    Node * tree = &seven;    
    seven.left = &three;    seven.right = &nine;
    three.left = &two;      three.right = &five;
    two.left = &one;
    five.left = &four;      five.right = &six;
    nine.left = &eight;
    
    tree_print(tree);       // 1 2 3 4 5 6 7 8 9
    return 0;
}

void tree_print(Node * tree) {

    // пустое дерево
    if (tree == NULL)
        return;                 // ничего не делаем, уходим
        
    // если дошли сюда, дерево НЕ пустое
    tree_print(tree->left);     // печатаем левое поддерево
    printf("%d ", tree->data);  // печатаем 7
    tree_print(tree->right);    // печатаем правое поддерево
}
```

Пусть дети сами разбираются со своими детьми. Бабушки не лезут печатать внуков.

## VIDEO

<p>Платформа:</p>

<p><iframe allowfullscreen="" height="315" src="https://plvideo.ru/embed/3F31Fqs6Jt1h" width="560"></iframe></p>

<p>Youtube:</p>
<p>Пока ссылка на полное видео</a>
<p><iframe allowfullscreen="" height="315" src="https://www.youtube.com/embed/FKCToOPxhEg" width="560"></iframe></p>


## Что будет напечатано R-D-L?

Что будет напечатано, если в функции печати порядок такой:

* печать правого поддерева, 
* печать данных в узле,
* печать левого поддерева.

![Бинарное дерево поиска](https://stepik.org/media/attachments/lesson/311164/btree.png)

```cpp
void tree_print(Node * tree) {

    // пустое дерево
    if (tree == NULL)
        return;                 // ничего не делаем, уходим
        
    // если дошли сюда, дерево НЕ пустое
    tree_print(tree->right);    // печатаем правое поддерево
    printf("%d ", tree->data);  // печатаем 7
    tree_print(tree->left);     // печатаем левое поддерево
}
```
Проверьте себя, запустив код с такой функцией печати. Почему так получилось?

## Что будет напечатано D-L-R?

Что будет напечатано, если в функции печати порядок такой:

* печать данных в узле,
* печать левого поддерева,
* печать правого поддерева. 

![Бинарное дерево поиска](https://stepik.org/media/attachments/lesson/311164/btree.png)

```cpp
void tree_print(Node * tree) {

    // пустое дерево
    if (tree == NULL)
        return;                 // ничего не делаем, уходим
        
    // если дошли сюда, дерево НЕ пустое
    printf("%d ", tree->data);  // печатаем 7
    tree_print(tree->left);     // печатаем левое поддерево
    tree_print(tree->right);    // печатаем правое поддерево
}
```
Проверьте себя, запустив код с такой функцией печати. Почему так получилось?

## VIDEO

<p>Платформа:</p>

<p><iframe allowfullscreen="" height="315" src="https://plvideo.ru/embed/05bItoSYRxDY" width="560"></iframe></p>

<p>Youtube:</p>
<p>Пока ссылка на полное видео</a>


## Обход в глубину и в ширину

Когда мы стремимся пройти как можно глубже по дереву, это называется **обход в глубину**.

Можно печатать по уровням (по "этажам" дерева). Это будет обходом в ширину. Его можно сделать с помощью очереди.

* Поместить корень в очередь.
* Пока очередь не пуста делать:
    * достать узел из очереди,
    * напечатать данные в узле,
    * поместить левого и правого ребенка (если они не NULL) в очередь.
    
