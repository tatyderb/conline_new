# Односвязный список - push

lesson = 308794


##  VIDEO

<p><iframe allowfullscreen="" height="315" src="https://www.youtube.com/embed/X_fUBjYpb0k" width="560"></iframe></p>

## Сколько элементов в списке

![Модель списка](https://stepik.org/media/attachments/lesson/308791/list1_model.png)

Напишем функцию size, которая возвращает сколько элементов в списке.

Для этого придется пройтись по всем узлам и сосчитать их. Сложность операции O(n).

Функция аналогична функции печати, только не печатаем, а увеличиваем счетчик узлов.

```cpp
int size(Node * list) {
    int n = 0;
    for (Node * p = list; p != NULL; p = p->next)
        n++;
    return n;
}
```

## Проверка на пустоту is_empty

Проверим пустой список или нет. Пусть функция возвращает ложь, если список не пустой и истину, если он пуст.

Работает. Но О(n):
```cpp
int is_empty(Node * list) {
    return size(list) == 0;
}
```

Это работающий, но очень плохой подход. Чтобы понять, пустой холодильник или нет, не нужно вытаскивать из него по 1 продукту и тщательно их пересчитывать. Пустота холодильника видна сразу.

Когда создавали список, он сразу был рабочим:
```cpp
Node * list = NULL;
```
Проверка на пустоту списка за О(1):
```cpp
int is_empty(Node * list) {
    return list == NULL;
}
```

## Тесты

Напишем тесты для функций is_empty, size, pop.

```cpp
int main() {
    Data test[] = {10, 3, 17, 21};

    Node * list = NULL;
    print(list);
    printf("size=%d : \n", size(list));                     // size = 0
    printf("Empty: %s\n", is_empty(list) ? "YES" : "NO");   // Empty: YES

    // тесты на push
    for(int i = sizeof(test)/sizeof(test[0]) - 1; i >= 0; i--) {
        push2(&list, test[i]);
        printf("push %d  size=%d : ", test[i], size(list));
        print(list);
    }

    printf("size=%d : \n", size(list));                     // size = 4
    printf("Empty: %s\n", is_empty(list) ? "YES" : "NO");   // Empty: NO

    // тесты на pop
    while( ! is_empty(list)) {
        Data d = pop(&list);
        printf("pop %d : ", d);
        print(list);
    }

    printf("size=%d : \n", size(list));                     // size = 0
    printf("Empty: %s\n", is_empty(list) ? "YES" : "NO");   // Empty: YES

    return 0;
}
```
Ожидаемый вывод:
```cpp

size=0 :
Empty: YES
push 21  size=1 : 21
push 17  size=2 : 17 21
push 3  size=3 : 3 17 21
push 10  size=4 : 10 3 17 21
size=4 :
Empty: NO
pop 10 : 3 17 21
pop 3 : 17 21
pop 17 : 21
pop 21 :
size=0 :
Empty: YES
```

## pop удаление верхнего узла из списка

Чтобы в функции push можно было изменить содержимое переменной list, нужно передать в функцию указатель на эту переменную.

![Модель списка](https://stepik.org/media/attachments/lesson/308793/list1_push_model.png)

list станет указывать на следующий элемент списка `list = list->next`. То есть list в функции должен измениться и вернуть значение, которое было на вершине списка. Значит вызов функции `x = pop(&list);`

Нужно освободить память (так как push захватывает память).

```cpp
Data pop(Node ** plist) {
    Node * p = *plist;      // p указывает на верхний узел списка
    Data res = p->data;     // res - число, которое было на вершине списка
    *plist = p->next;       // list стал указывать на следующий узел
    free(p);                // удаленный узел - освободили память
    return res;             // вернули значение, которое было на вершине списка
}
```

## Найдите ошибку

Этот pop короче, но не работает. Найдите ошибку.

```cpp
Data pop(Node ** plist) {
    Node * p = *plist;      // p указывает на верхний узел списка
    *plist = p->next;       // list стал указывать на следующий узел
    free(p);                // удаленный узел - освободили память
    return p->data;         // вернули значение, которое было на вершине списка
}
```

Ответ: после `free(p)` (освободили эту память) бесполезно обращаться к ее части. Иногда это может работать. Но иногда это может возвращать другое число. Получим плавающую ошибку, которую трудно найти.
