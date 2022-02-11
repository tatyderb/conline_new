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
    * `Data` **list_pop_front** `(struct Node * list);` - удаляет голову списка, возвращает данные из удаленного узла.
    * `Data` **list_pop_back** `(struct Node * list);` - удаляет хвост списка, возвращает данные из удаленного узла.
    * `Data` **list_delete** `(struct Node * t);` - удаляет узел t из списка, возвращает данные из удаленного узла.
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

Data list_pop_front(struct Node * list);
Data list_pop_back(struct Node * list);
Data list_delete(struct Node * t);

void list_print (struct Node * list);
int list_is_empty(struct Node * list);

void list_clear(struct Node * list);
```

Объявление структуры, прототипы функций и реализацию функции main посылать не нужно. Проверку корректности аргументов не делать.

*Гарантируется, что набор тестов удовлетворяет следующим требованиям: все команды remove и delete корректны, то есть при их исполнении в списке содержится хотя бы один элемент.*

Тут нужно привести код тестов. Если вы не видите его, напишите.

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
void test1();
void test2();
void test3();
void test4();
void test5();

int main()
{
    int n;  // test number
    scanf("%d", &n);
    
    switch(n){
        case 1:
            test1();
            break;
        case 2:
            test2();
            break;
        default:
            fprintf(stderr, "Test %d not implemented yet!\n", n);
    }
    
    printf("end\n");
    return 0;
}

void test1()
{
    // init + is_empty
    
	struct Node a;
		
	list_init(&a);
	assert(list_is_empty(&a));
}
void test2()
{
	struct Node * x = malloc(11*sizeof(struct Node));
	struct Node * a = x+10;
	
	list_init(a);
	assert(list_is_empty(a));
	
	for(int i = 0; i < 10; i++) {
		x[i].data = i;
		list_insert(a, &x[i]);
	}
	list_print(a);              // 9 8 7 6 5 4 3 2 1 0
	assert(!list_is_empty(a));
    
    free(x);
}

void test3()
{
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



