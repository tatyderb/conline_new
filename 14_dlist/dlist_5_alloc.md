# Двусвязный список. Создание узла

lesson = 308800


##  VIDEO

<p><iframe allowfullscreen="" height="315" src="https://www.youtube.com/embed/obY-A7G1YeU" width="560"></iframe></p>


## Тестирование

Тесты на добавление и удаление с выделением памяти хорошо бы начать на новом списке. Старые тесты не надо выбрасывать. Лучше оформить их в функцию `void test()` и сейчас дописать тесты в отдельную функцию `void test_alloc()`. Ее мы будем вызывать из `main`. Функцию `test` пока вызывать не будем. Потом, когда у нас будут написаны новые тесты, написаны и отлажены функции, мы включим старые тесты и будем выполнять все тесты, чтобы убедиться, что мы ничего не сломали.

```cpp
void test_alloc() {
    Node * list = malloc(sizeof(Node));
    list_init(list);
    list_print(list);                    // пустой список
    
    Node * t;
    t = list_push_front(list, 21);
    printf("push %d: ", t->data);
    list_print(list);                    // 21
    
    free(list);
}
int main() {
    // test_no_malloc();    // старые тесты оформим отдельной функцией
                            // и пока не будем вызывать
    test_alloc();           // новые тесты, пока запускаем только их
    return 0;
}
```

## list_push_front

По использованию функции `t = list_push_front(list, 21);` можно написать прототип:

```cpp
Node * list_push_front(Node * list, Data d);
```
Реализуем функцию. Сначала создадим узел, выделив для него динамическую память. Узел типа Node, значит памяти нужно выделять `sizeof(Node)`.

```cpp
Node * list_push_front(Node * list, Data d) {
    Node * p = malloc(sizeof(Node));    // выделили память под узел
    p->data = d;                        // записали в узел данные
    list_insert(list, p);               // вставили узел в начало списка
    return p;                           // вернули указатель на новый узел
}
```
Заметим, что вставляем новый узел функцией `list_insert`, а не пишем еще раз код вставки, плодя потенциальные ошибки.

Проверяем программу под valgrind. Пока не обращаем внимание на утечки памяти, так как в тестах память выделяется, но не освобождается.

## Тесты на push_front и push_back

Напишем тесты и определим ожидаемый вывод.
```cpp
void test_alloc() {
    Data test_data1[] = {21, 17, 3};    // для вставки сначала
    Data test_data2[] = {10, 8};        // для вставки с конца
    
    Node * list = malloc(sizeof(Node));
    list_init(list);
    list_print(list);                    // пустой список
    
    Node * t;
    for(size_t i = 0; i < sizeof(test_data1)/sizeof(test_data1[0]); i++) {
        t = list_push_front(list, test_data1[i]);
        printf("push_front %d: ", t->data);
        list_print(list);
    }
    // 3 17 21

    for(size_t i = 0; i < sizeof(test_data2)/sizeof(test_data2[0]); i++) {
        t = list_push_back(list, test_data2[i]);
        printf("push_back %d: ", t->data);
        list_print(list);
    }
    // 3 17 21 10 8
    
    free(list);
}
```
Ожидаемый вывод:
```cpp

push_front 21: 21
push_front 17: 17 21
push_front 3: 3 17 21
push_back 10: 3 17 21 10
push_back 8: 3 17 21 10 8
```

## Реализуем push_back

Реализуйте сами.

Если у вас код функции занимает больше 1 строки, перечитайте, как мы писали `list_insert_before`.
