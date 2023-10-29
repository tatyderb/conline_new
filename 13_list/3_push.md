# Односвязный список - push

lesson = 308793


##  VIDEO

<p><iframe allowfullscreen="" height="315" src="https://www.youtube.com/embed/BGaTG_IACXE" width="560"></iframe></p>

## push возвращает указатель на первый узел

![Модель списка](https://stepik.org/media/attachments/lesson/308793/list1_push_model.png)

Добавим узел t в начало списка, перед узлом a. Тогда у узла t следующим будет узел а `t.next = &a` и переменная list, которая указывает на начало списка, будет указывать на t `list = &t`.

Заметим, что list содержит указатель на a, т.е. `t.next = list`

Избавимся от модели, перейдем к использованию только переменной list и переменной p, которая указывает на t.

```cpp
Node * p = &t;
p->next = list; // t.next = list;
list = p;       // list = &t;
```
Оформим в виде функции `list = push(list, &t)`, так как значение переменной list должно измениться:

```cpp
Node * push(Node * list, Node * p) {
    p->next = list;
    list = p;
    return list;
    // return p;    вместо последних 2 строк
}
int main() {
    ...
    list = push(list, &t);
    ...
}
```

## Вариант 2. push ничего не возвращает

Чтобы в функции push можно было изменить содержимое переменной list, нужно передать в функцию указатель на эту переменную.

![Модель списка](https://stepik.org/media/attachments/lesson/308793/list1_push_model.png)

```cpp
void push(Node ** plist, Node * p) {
    p->next = *plist;
    *plist = p;
}
int main() {
    ...
    push(&list, &t);
    ...
}
```

## push выделяет память

Хотим передавать функции push не уже созданный узел, а число типа Data. Чтобы push сам выделял память динамически и вставлял сделанный узел.

```cpp
void push(Node ** plist, Data d) {
    Node * p = malloc(sizeof(Node));
    p->data = d;
    p->next = *plist;
    *plist = p;
}
int main() {
    ...
    push(&list, 10);
    ...
}
```

## Избавимся от модели, добавим тесты

После реализации push модель больше не нужна. Можно сделать `Node * list = NULL` и дальше добавлять узлы с помощью push.

Изменим тесты в main:
```cpp
int main() {
    Node * list = NULL;
    print(list);        // ничего не печатает
    
    push(&list, 21);    // 21
    print(list);
    
    push(&list, 17);    // 17 21
    print(list);
    
    push(&list, 3);     // 3 17 21
    print(list);
    
    push(&list, 10);    // 10 3 17 21
    print(list);
    
    return 0;
}
```
Перепишем через цикл и массив тестовых данных:
```cpp
int main() {
    Data test[] = {10, 3, 17, 21};
    
    Node * list = NULL;
    print(list);
    for(int i = sizeof(test)/sizeof(test[0]) - 1; i >= 0; i--) {
        push(&list, test[i]);
        print(list);
    }
    
    return 0;
}
```
Output:
```cpp

21
17 21
3 17 21
10 3 17 21
```
При запуске с valgrind видим, что ошибок нет, но есть утечка памяти. Пора реализовать функцию pop.
