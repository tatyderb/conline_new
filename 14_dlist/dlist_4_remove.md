# Двусвязный список. Удаление узла

lesson = 308799


##  VIDEO

<p><iframe allowfullscreen="" height="315" src="https://www.youtube.com/embed/a1SHkevSt7Y" width="560"></iframe></p>


## Удаление

Удалим узел u. Нужно вместо стрелок 1, 2, 3, 4 восстановить серые стрелки.

![Вставка узла в двусвязный список](https://stepik.org/media/attachments/lesson/308798/dlist_insert.png)

Что передать функции, которая удаляет узел? Хватит ли указателя на сам узел или нужны указатели на следующий или предыдущий узел?

Так как указатели на следующий и предыдущий узел можно вычислить, то хватит указателя на удаляемый узел:
```cpp
list_remove(&u);
```

Реализация:
```cpp
void list_remove(Node * t) {
    Node * p = t->prev;
    Node * q = t->next;
    p->next = q;
    q->prev = p;
}
```

## API работающее с узлами без выделения и освобождения памяти

```cpp
void list_init(Node * list);

void list_insert(Node * list, Node * t);
void list_insert_before(Node * list, Node * t);
void list_remove(Node * t);
```

Эти функции работают с уже готовыми узлами. Нужно добавить набор функций, которые будут создавать узел и разрушать его, освобождая память:

```cpp
Node * list_push_front(Node * list, Data d);    // добавить в начало списка
Node * list_push_back(Node * list, Data d);     // добавить в конец списка

Data list_pop_front(Node * list);   // удалить из начала списка
Data list_pop_back(Node * list);    // удалить из конца списка
Data list_delete(Node * t);         // удалить узел t

void list_clear(Node * list);       // удалить все, кроме замочка

```