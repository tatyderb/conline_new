# Задачи на списки

lesson = 659477
lang = c_valgrind

## TASKINLINE list_2 Двусвязный список

Реализуйте структуру данных "двусвязный список". Для этого при объявленных структурах Node (один элемент списка)
```cpp
typedef int Data;
struct Node {
	struct Node * next;
	struct Node * prev;
	Data data;
};
```
* **data** - данные, хранящиеся в одном элементе,
* **next** - указатель на следующий элемент списка (для конца списка - сам список)
* **prev** - указатель на предыдущий элемент списка (для начала списка - сам список)

Реализуйте функции работы со списком.

* Без выделения и освобождения памяти:
    * `void` **list_init** `(struct Node * list);` - инициализация пустого списка.
    * `void` **list_insert** `(struct Node * list, struct Node * t);` - вставляет элемент t после элемента list
    * `void` **list_insert_before** `(struct Node * list, struct Node * t);` - вставляет элемент t перед элементом list
    * `void` **list_remove** `(struct Node * t);` -	удаляет элемент t из списка
* С выделением и освобождением памяти:
    * `struct Node *` **list_push_front** `(struct Node * list, Data d);` - выделяет память под новый элемент, содержащий данные d, и вставляет его в **голову** списка. Возвращает указатель на этот новый элемент или NULL, если произошла ошибка.
    * `struct Node *` **list_push_back** `(struct Node * list, Data d);` - выделяет память под новый элемент, содержащий данные d, и вставляет его в **хвост** списка. Возвращает указатель на этот новый элемент или NULL, если произошла ошибка.
    * `Data` **list_delete** `(struct Node * t);` - удаляет узел t из списка, возвращает данные из удаленного узла.
    * `Data` **list_pop_front** `(struct Node * list);` - удаляет голову списка, возвращает данные из удаленного узла.
    * `Data` **list_pop_back** `(struct Node * list);` - удаляет хвост списка, возвращает данные из удаленного узла.
    * `void` **list_clear** `(struct Node * list);`	опустошает список, освобождая память. После этого можно опять добавлять элементы в список.
* Прочие функции:    
    * `void` **list_print** `(struct Node * list);`	распечатывает через пробел числа, лежащие в списке. С самого первого до последнего. В конце переводит строку. Полезна для отладки прочих функций.
    * `int` **list_is_empty** `(struct Node * list);`	проверяет пустой это список или нет

Рекомендуем реализовывать циклический список с барьерным элементом. Но вы можете реализовать любой список с указанным API.

![циклический список с барьерным элементом](https://stepik.org/media/attachments/lesson/308797/dlist_barier_model.png)

```cpp
void list_init(struct Node * list);

void list_insert(struct Node * list, struct Node * t);
void list_insert_before(struct Node * list, struct Node * t);
void list_remove(struct Node * t);

struct Node * list_push_front(struct Node * list, Data d);
struct Node * list_push_back(struct Node * list, Data d);

Data list_delete(struct Node * t);
Data list_pop_front(struct Node * list);
Data list_pop_back(struct Node * list);

void list_print (struct Node * list);
int list_is_empty(struct Node * list);

void list_clear(struct Node * list);
```

Объявление структуры, прототипы функций и реализацию функции main посылать не нужно. Проверку корректности аргументов не делать.

*Гарантируется, что набор тестов удовлетворяет следующим требованиям: все команды remove и delete корректны, то есть при их исполнении в списке содержится хотя бы один элемент.*

```cpp
void test_non_alloc(int n)
{
	struct Node * x = malloc(11*sizeof(struct Node));
	struct Node * a = x+10;
	
	list_init(a);
	assert(list_is_empty(a));
    if(n == 1) 
        goto END;
	
	for(int i = 0; i < 10; i++) {
		x[i].data = i;
		list_insert(a, &x[i]);
	}
	list_print(a);              // 9 8 7 6 5 4 3 2 1 0
	assert(!list_is_empty(a));
    if(n == 2) 
        goto END;
    
	list_remove(&x[5]);
	list_print(a);              // 9 8 7 6 4 3 2 1 0
	list_remove(&x[0]);
	list_print(a);              // 9 8 7 6 4 3 2 1
	list_remove(&x[9]);
	list_print(a);              // 8 7 6 4 3 2 1
    if(n == 3) 
        goto END;
    
	list_insert_before(a, &x[0]);
	list_print(a);              // 8 7 6 4 3 2 1 0
	list_insert(a, &x[9]);
	list_print(a);              // 9 8 7 6 4 3 2 1 0
	list_insert(&x[6], &x[5]);
	list_print(a);              // 9 8 7 6 5 4 3 2 1 0
    if(n == 4) 
        goto END;

	while(!list_is_empty(a))
		list_remove(a->next);
    if(n == 5) 
        goto END;
    
END:
    free(x);
}

void test_alloc(int n)
{
	struct Node a0, b0;
	struct Node * a = &a0;
	struct Node * b = &b0;
	
	list_init(a);
	list_init(b);
    
    int i;
	for(i=0; i<10; i++)
		list_push_back(a, i);
	list_print(a);              // 0 1 2 3 4 5 6 7 8 9
	assert(list_is_empty(b));
	if (n == 6)
        goto END;
	
	for(i=0; i<10; i++)
		list_push_front(b, list_pop_back(a));
	list_print(b);              // 0 1 2 3 4 5 6 7 8 9
	assert(list_is_empty(a));
	if (n == 7)
        goto END;
	
	for(i=0; i<10; i++) {
		list_push_front(a, i); 
		list_pop_front(b);
	}
	list_print(a);              // 9 8 7 6 5 4 3 2 1 0
	assert(list_is_empty(b));
	if (n == 8)
        goto END;

	for(i=0; i<10; i++)
		list_push_back(b, list_pop_front(a));
	list_print(b);              // 9 8 7 6 5 4 3 2 1 0
	assert(list_is_empty(a));
	if (n == 9)
        goto END;
        
    // 10. Тест на clear
    for(i=0; i<10; i++)
		list_push_back(a, i);
	list_clear(a);
    assert(list_is_empty(a));
	if (n == 10)
        goto END;

END:	
	list_clear(a);
	list_clear(b);
}
```
**Если ваш код содержит ошибку, но тесты проходят, пришлите ваш код с указанием ошибки и особая благодарность, если вы придумаете тест, который ошибку ловит.**

HEADER
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <malloc.h>

typedef int Data;

struct Node {
	struct Node * next;
	struct Node * prev;
	Data data;
};

void list_foreach(struct Node * list, void (*func)(Data d, void * param), 
    void * param);
// list_foreach(list, print_it, stderr);
/* 
void print_it(Data d, void * param)
{
	FILE * fd = param;
	fprintf(fd, "%d ", d);
}
*/

void list_init(struct Node * list);

// no alloc
void list_insert(struct Node * list, struct Node * t);	
		    // insert t after element list
void list_insert_before(struct Node * list, struct Node * t);	
		    // insert t before element list
void list_remove(struct Node * list);

// alloc 
struct Node * list_push_front(struct Node * list, Data d); 
		    // return newly inserted node
struct Node * list_push_back(struct Node * list, Data d);  
		    // return newly inserted node
Data list_pop_front(struct Node * list); // remove list head, return its data
Data list_pop_back(struct Node * list);  // remove list tail, return its data
Data list_delete(struct Node * list);  // return newly inserted node
void list_clear(struct Node * list);	// prepare to insert again!

int  list_is_empty(struct Node * list);
void list_print(struct Node * list);

// tests:
void test_alloc(int test_number);
void test_non_alloc(int test_number);

int main()
{
    int n;  // test number
    scanf("%d", &n);
    
    switch(n){
        case 1:         // init + is_empty
        case 2:         // insert + print
        case 3:         // remove
        case 4:         // insert_before + insert_after
        case 5:         // remove all
            test_non_alloc(n);
            break;
        case 6:         // push_back
        case 7:         // push_front + pop_back
        case 8:         // push_back
        case 9:         // push_back
        case 10:        // clear
            test_alloc(n);
            break;
        default:
            fprintf(stderr, "Test %d not implemented yet!\n", n);
    }
    
    printf("end\n");
    return 0;
}

void test_non_alloc(int n)
{
	struct Node * x = malloc(11*sizeof(struct Node));
	struct Node * a = x+10;
	
	list_init(a);
	assert(list_is_empty(a));
    if(n == 1) 
        goto END;
	
	for(int i = 0; i < 10; i++) {
		x[i].data = i;
		list_insert(a, &x[i]);
	}
	list_print(a);              // 9 8 7 6 5 4 3 2 1 0
	assert(!list_is_empty(a));
    if(n == 2) 
        goto END;
    
	list_remove(&x[5]);
	list_print(a);              // 9 8 7 6 4 3 2 1 0
	list_remove(&x[0]);
	list_print(a);              // 9 8 7 6 4 3 2 1
	list_remove(&x[9]);
	list_print(a);              // 8 7 6 4 3 2 1
    if(n == 3) 
        goto END;
    
	list_insert_before(a, &x[0]);
	list_print(a);              // 8 7 6 4 3 2 1 0
	list_insert(a, &x[9]);
	list_print(a);              // 9 8 7 6 4 3 2 1 0
	list_insert(&x[6], &x[5]);
	list_print(a);              // 9 8 7 6 5 4 3 2 1 0
    if(n == 4) 
        goto END;

	while(!list_is_empty(a))
		list_remove(a->next);
    if(n == 5) 
        goto END;
    
END:
    free(x);
}

void test_alloc(int n)
{
	struct Node a0, b0;
	struct Node * a = &a0;
	struct Node * b = &b0;
	
	list_init(a);
	list_init(b);
    
    int i;
	for(i=0; i<10; i++)
		list_push_back(a, i);
	list_print(a);              // 0 1 2 3 4 5 6 7 8 9
	assert(list_is_empty(b));
	if (n == 6)
        goto END;
	
	for(i=0; i<10; i++)
		list_push_front(b, list_pop_back(a));
	list_print(b);              // 0 1 2 3 4 5 6 7 8 9
	assert(list_is_empty(a));
	if (n == 7)
        goto END;
	
	for(i=0; i<10; i++) {
		list_push_front(a, i); 
		list_pop_front(b);
	}
	list_print(a);              // 9 8 7 6 5 4 3 2 1 0
	assert(list_is_empty(b));
	if (n == 8)
        goto END;

	for(i=0; i<10; i++)
		list_push_back(b, list_pop_front(a));
	list_print(b);              // 9 8 7 6 5 4 3 2 1 0
	assert(list_is_empty(a));
	if (n == 9)
        goto END;
        
    // 10. Тест на clear
    for(i=0; i<10; i++)
		list_push_back(a, i);
	list_clear(a);
    assert(list_is_empty(a));
	if (n == 10)
        goto END;

END:	
	list_clear(a);
	list_clear(b);
}

#line 10000
TEST
1
----
end
====
2
----
9 8 7 6 5 4 3 2 1 0 
end
====
3
----
9 8 7 6 5 4 3 2 1 0 
9 8 7 6 4 3 2 1 0 
9 8 7 6 4 3 2 1 
8 7 6 4 3 2 1 
end
====
4
----
9 8 7 6 5 4 3 2 1 0 
9 8 7 6 4 3 2 1 0 
9 8 7 6 4 3 2 1 
8 7 6 4 3 2 1 
8 7 6 4 3 2 1 0 
9 8 7 6 4 3 2 1 0 
9 8 7 6 5 4 3 2 1 0 
end
====
5
----
9 8 7 6 5 4 3 2 1 0 
9 8 7 6 4 3 2 1 0 
9 8 7 6 4 3 2 1 
8 7 6 4 3 2 1 
8 7 6 4 3 2 1 0 
9 8 7 6 4 3 2 1 0 
9 8 7 6 5 4 3 2 1 0 
end
====
6
----
0 1 2 3 4 5 6 7 8 9
end
====
7
----
0 1 2 3 4 5 6 7 8 9
0 1 2 3 4 5 6 7 8 9
end
====
8
----
0 1 2 3 4 5 6 7 8 9
0 1 2 3 4 5 6 7 8 9
9 8 7 6 5 4 3 2 1 0
end
====
9
----
0 1 2 3 4 5 6 7 8 9
0 1 2 3 4 5 6 7 8 9
9 8 7 6 5 4 3 2 1 0
9 8 7 6 5 4 3 2 1 0
end
====
10
----
0 1 2 3 4 5 6 7 8 9
0 1 2 3 4 5 6 7 8 9
9 8 7 6 5 4 3 2 1 0
9 8 7 6 5 4 3 2 1 0
end
====


## TASKINLINE list_3 Пьяница

В игре в пьяницу карточная колода раздается поровну двум игрокам. Далее они вскрывают по одной верхней карте, и тот, чья карта старше, забирает себе обе вскрытые карты, которые кладутся под низ его колоды (сначала кладется карта от первого игрока, потом - от второго). Тот, кто остается без карт – проигрывает.

Для простоты будем считать, что все карты различны по номиналу, а также, что самая младшая карта побеждает самую старшую карту ("шестерка берет туза").

Игрок, который забирает себе карты, сначала кладет под низ своей колоды карту первого игрока, затем карту второго игрока (то есть карта второго игрока оказывается внизу колоды).

Напишите программу, которая моделирует игру в пьяницу и определяет, кто выигрывает. 

* В игре участвует 10 карт, имеющих значения от 0 до 9, 
* большая карта побеждает меньшую, 
* карта со значением 0 побеждает карту 9.

### Входные данные

Программа получает на вход две строки: первая строка содержит 5 карт первого игрока, вторая – 5 карт второго игрока. Карты перечислены сверху вниз, то есть каждая строка начинается с той карты, которая будет открыта первой.

### Выходные данные

Программа должна определить, кто выигрывает при данной раздаче, и вывести слово **first** или **second**, после чего вывести количество ходов, сделанных до выигрыша. 

Если на протяжении $10^6$ ходов игра не заканчивается, программа должна вывести слово **botva**.

Реализовать колоды игроков через очереди на основе двухсвязных списков.

Условия задачи взяты из [дистанционной подготовки по информатике для школьников](http://informatics.mccme.ru/moodle/mod/statements/view3.php?id=206&chapterid=50), автор не указан

Отладочная печать на каждой итерации цикла для раздачи карт из примера:
```cpp
1 3 5 7 9
2 4 6 8 0
----
3 5 7 9
4 6 8 0 1 2
----
5 7 9
6 8 0 1 2 3 4
----
7 9
8 0 1 2 3 4 5 6
----
7 9
8 0 1 2 3 4 5 6
----
9
0 1 2 3 4 5 6 7 8
----

0 1 2 3 4 5 6 7 8
second 5
```

### Алгоритм решения (для совсем слабых духом)

Для написания этой программы достаточно реализовать структуру "очередь" и дальше смоделировать все то, о чём написано в условии. А именно:

* Задаём цикл for(i: 0 .. N) на N = 10^6 итераций.
* При каждом заходе в цикл берём по первому элементу из очередей, эмулирующих колоды первого и второго игроков.
    * Сравниваем их согласно описанной в условии методике.
    * Добавляем две взятые карты к конец колоды-очереди игрока выигравшего на данном сравнении.
    * Если при очередной итерации одна из очередей оказывается пуста, то выводим победителя и количество совершённых итераций (i).
* Если все 10^6 итераций успешно выполнились - выводим "botva".

**Теста на botva нет. Если кто-то найдет входную последовательность, чтобы у нас был тест на ботву, мы будем очень благодарны. А пока лучше сделаем еще одну задачу. Свою.**

TEST
1 3 5 7 9
2 4 6 8 0
----
second 5
====
2 4 6 8 0
1 3 5 7 9
----
first 5
====
1 4 5 8 9
2 3 6 7 0
----
first 31
====
1 4 5 8 0
2 3 6 7 9
----
first 9
====
1 3 4 7 8
0 2 5 6 9
----
second 101
====
1 7 8 6 4 
2 4 6 7 9
----
botva
====

## SKIP TASKINLINE Акулина

**Два игрока** `Gamer0` и `Gamer1` играют в карточную игру Акулина (Witch).

Дана [колода карт](https://stepik.org/lesson/607327/step/1?unit=602468)

Из колоды по очереди каждому игроку раздается по 1 карте, пока не закончатся карты в колоде.

Дальше игроки сбрасывают парные карты по правилам:

* Пиковую даму `Qs` сбрасывать нельзя.
* Любую другую даму можно сбрасывать одну.
* Остальные карты сбрасываются **парой** одинакового достоинства без учета масти, например, `6h` и `6s`.

После сброса карт игрок отдает первую карту следующему игроку. Получивший карту игрок сбрасывает карты с руки, если есть пары.
Начинает отдавать `Gamer0`. (Если бы игроков было больше 2, то они отдавали бы карты по кругу).
Когда у одно игрока осталась единственная карта `Qs` (Акулина, ведьма), то игра заканчивается. Этот игрок проиграл.

При этом печатается отладочная печать. 

* Сначала печатается номер игрока (от 0) по формату `Gamer%d`, его рука.
    * потом сброс карт, пара ищется с начала, сбрасывается первая парная комбинация. Если на руке `JsJhJc`, то сброшена будет `Js` и `Jh`.
* Игрок передает **первую** карту в руке другому игроку.
    * печатается рука обоих игроков, кто отдал и кто получил карту.
    * печатается сброс игрока, который получил карту (если есть).
* в конце печатается какой игрок проиграл.  

TEST
AsAcJhTd6sThQdQs6d7cJc7h
----
Gamer0: AsJh6sQd6dJc
drop Jh Jc: As6sQd6d
drop 6s 6d: AsQd
drop Qd: As
Gamer1: AcTdThQs7c7h
drop Td Th: AcQs7c7h
drop 7c 7h: AcQs
Get card As from Gamer0 to Gamer1
Gamer0:
Gamer1: AcQsAs
drop Ac As: Qs
Gamer1 is witch!
====
As8hQs8dAc
----

