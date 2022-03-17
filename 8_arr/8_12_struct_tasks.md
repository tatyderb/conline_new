# Задачи со структурами

lesson = 607327
lang = c_valgrind

## Пример: хранение карт

Напишем часть кода для игры с [игральными картами](https://ru.wikipedia.org/wiki/%D0%98%D0%B3%D1%80%D0%B0%D0%BB%D1%8C%D0%BD%D1%8B%D0%B5_%D0%BA%D0%B0%D1%80%D1%82%D1%8B), например, для [покера](https://ru.wikipedia.org/wiki/%D0%9F%D0%BE%D0%BA%D0%B5%D1%80).

Для хранения 1 карты объявим структуру с полями **suit** (масть) и **rank** (достоинство).

```cpp
struct Card {
    char rank;    // достоинство
    char suit;    // масть
};
```

Для кодирования карт используют обозначения:

* Масть (suit):
    * **c** - clubs, трефы, ♣
    * **s** - spades, пики, ♠️
    * **h** - hearts, червы, ♥️
    * **d** - diamond, бубны, ♦️
* Достоинство (rank):
    * '2', '3', '4', '5', '6', '7', '8', '9' - от 2 до 9
    * 'T' (ten - десять), 
    * 'J' (валет), 
    * 'Q' (дама), 
    * 'K' (король), 
    * 'A' (туз).
    
В этой нотации *дама пик* и *король бубен* записываются как `QsKd`.

![колода с джокерами](https://upload.wikimedia.org/wikipedia/commons/thumb/a/a6/Atlasnye_playing_cards_deck_2.svg/700px-Atlasnye_playing_cards_deck_2.svg.png)

Напишем функции, которые печатают набор карт в указанном формате и из строки в этом формате создают массив карт.

Дальше мы будем писать функции, которые проверяют набор карт в руке, поэтому массив карт будем называть `hand` (рука). В массиве последняя карта "фальшивая" с мастью 0 и достоинством 0.

```cpp
void print_cards(struct Card * hand);
int read_cards(struct Card * hand);
```

### Функция печати карт

В функции main создадим массив карт (с "фальшивой" последней картой в конце). Перебираем карты в цикле до "фальшивой" карты, которая обозначает конец карт в руке:
```cpp
#include <stdio.h>

struct Card {
    char rank;    // достоинство
    char suit;    // масть
};

int main()
{
    struct Card hand [] = {{'Q', 's'}, {'A','h'}, {'9', 'd'}, {0, 0}};
    
    // напечатаем карты до фальшивой, фальшивую не печатаем:
    for(int i = 0; hand[i].rank != 0; i++)
        printf("%c%c", hand[i].rank, hand[i].suit);
    printf("\n");
    return 0;
}
```
Перепишем цикл через указатель, `p` - указатель на одну карту. Сначала он указывает на первую карту руки `&hand[0]` или `&*(hand+0)`, оно же просто `hand`.

`p++` перемещает указатель на *следующую* ***карту***.
```cpp
    struct Card * p;    // указатель на одну карту
    for(p = hand; p->rank != 0; p++)
        printf("%c%c", p->rank, p->suit);
    printf("\n");    
```
Оформим этот код в виде отдельной функции печати массива карт до фальшивой карты.
```cpp
void print_cards(struct Card * hand)
{
    struct Card * p;    // указатель на одну карту
    for(p = hand; p->rank != 0; p++)
        printf("%c%c", p->rank, p->suit);
    printf("\n");    
}
```
Функция main:
```cpp
int main()
{
    struct Card hand [] = {{'Q', 's'}, {'A','h'}, {'9', 'd'}, {0, 0}};
    print_cards(hand);
    return 0;
}
```

### Функция чтения карт

Колода 52 карты, +1 "фальшивая" обозначает конец карт. Значит в массиве не может быть больше 53 карт.

Прочитаем и сразу для проверки напечатаем карты. Входная и выходная строка должна совпасть.
```cpp
#define DECKSIZE 52
int main()
{
    struct Card hand[DECKSIZE+1];
    read_cards(hand);
    print_cards(hand);
    
    return 0;
}    
```
Символы будем читать парами, ожидая в паре достоинство и масть. Мы умеем читать [неизвестное количество чисел с помощью функции scanf](https://stepik.org/lesson/604863/step/2?unit=599967). Аналогично прочитаем неизвестное количество пар символов.
```cpp
void read_cards(struct Card * hand)
{
    struct Card * p;    // указатель на одну карту
    for(p = hand; 2 == scanf("%c%c", &p->rank, &p->suit); p++)
        ;
    // в конец положим фальшивую карту
    p->rank = p->suit = 0;
}
```
Такой подход работает, если у нас после карт не будет, например, двух пробельных символов. Тогда будет ошибка. Хорошо бы проверять, что читаем именно карты, а если прочли не карту, завершать чтение:
```cpp
void read_cards(struct Card * hand)
{
    struct Card * p;    // указатель на одну карту
    for(p = hand; 2 == scanf("%c%c", &p->rank, &p->suit); p++) {
        if (!valid_card(p))
            break;
    }
    // в конец положим фальшивую карту
    p->rank = p->suit = 0;
}
int valid_card(struct Card * card)
{
    char * const suit = "cshd";        // в строках в конце тоже есть "фальшивый" символ '\0'
    char * const rank = "23456789TJQKA";
    int i;
    for (i = 0; suit[i] != '\0'; i++)
        if (suit[i] == card->suit)      // масть такая существует
            break;
    if (suit[i] == '\0')                // в card->suit была неправильная масть
        return 0;
        
    for (i = 0; rank[i] != '\0'; i++)
        if (rank[i] == card->rank)      // достоинство такое существует
            return 1;                   // масть и достоинство существуют, карта правильная
            
    return 0;                           // в card->rank было неправильное достоинство
}
```
Не забывайте писать прототипы функций (или реализацию) раньше первого вызова функции.

Заметьте, что функция чтения имеет уязвимость. Она не проверяет сколько карт уже считано и можно ввести больше карт, чем выделено памяти под массив. Подумайте, как можно изменить функцию, чтобы она гарантированно не писала вне переданного массива. 

## TASKINLINE struct_card Пиковая дама

Реализуйте функцию, которая ищет пиковую даму в переданной руке.

`int check(struct Card * hand);`

`hand` - указатель на массив карт, последняя карта в котором имеет достоинство 0 (именно 0, а не '0', это фальшивая карта, используется только для обозначения конца массива).

Функция возвращает 1, если в руке есть пиковая дама, иначе возвращает 0.

Посылать только реализацию функции.

Не забудьте проверить свой код. Например, так:
```cpp
int main()
{
    struct Card hand1 [] = {{'Q', 's'}, {'A','h'}, {'9', 'd'}, {0, 0}};
    struct Card hand2 [] = {{'2', 's'}, {'A','h'}, {0, 0}};
    assert(1 == check(hand1));
    assert(0 == check(hand2));
    
    return 0;
}
```
HEADER
#include <stdio.h>

struct Card {
    char rank;    // достоинство
    char suit;    // масть
};

int valid_card(struct Card * card)
{
    char * const suit = "cshd";        // в строках в конце тоже есть "фальшивый" символ '\0'
    char * const rank = "23456789TJQKA";
    int i;
    for (i = 0; suit[i] != '\0'; i++)
        if (suit[i] == card->suit)      // масть такая существует
            break;
    if (suit[i] == '\0')                // в card->suit была неправильная масть
        return 0;
        
    for (i = 0; rank[i] != '\0'; i++)
        if (rank[i] == card->rank)      // достоинство такое существует
            return 1;                   // масть и достоинство существуют, карта правильная
            
    return 0;                           // в card->rank было неправильное достоинство
}
void read_cards(struct Card * hand)
{
    struct Card * p;    // указатель на одну карту
    for(p = hand; 2 == scanf("%c%c", &p->rank, &p->suit); p++) {
        if (!valid_card(p))
            break;
    }
    // в конец положим фальшивую карту
    p->rank = p->suit = 0;
}
void print_cards(struct Card * hand)
{
    struct Card * p;    // указатель на одну карту
    for(p = hand; p->rank != 0; p++)
        printf("%c%c", p->rank, p->suit);
    printf("\n");    
}
int main()
{
    struct Card hand[100];
    
    read_cards(hand);
    print_cards(hand);
    printf("%d\n", check(hand));

    return 0;
}

TEST
QsAh9d
---
QsAh9d
1
====
2s8sAsKsTs
---
2s8sAsKsTs
0
====
Th
----
Th
0
====
Qs
----
Qs
1
====
AcQcTcKcJc
----
AcQcTcKcJc
0
====
AsKsQsJsTs
----
AsKsQsJsTs
1
====
2h3h4h5h6h
----
2h3h4h5h6h
0
====
2s9dThKc5s
----
2s9dThKc5s
0
====
2h3h4hQs
----
2h3h4hQs
1
====
2h3hQs
----
2h3hQs
1
====
2hQs
----
2hQs
1
====

## TASKINLINE elong_print Печать длинного числа


В Си целые числа ограничены типами unsigned long long int. Чтобы работать с большими числами нужно придумать как их хранить и написать функции для работы с ними.

Число 147 это $7 \cdot 10^0 + 4 \cdot 10^1 + 1 \cdot 10^2$. 

можно представить любое число $a$ как 
 $a_0 \cdot 10^0 + a_1 \cdot 10^1 + a_2 \cdot 10^2$
 
 Будем хранить коэффициенты $a_0$, $a_1$, $a_2$ в массиве `a` как `a[0]`, `a[1]`, `a[2]`. И будем в `n` хранить максимальную степень 10 в разложении числа по степеням 10.

Объединим массив `a` и поле `n` в структуру `Decimal`, так как они описывают одно и то же число. Чисел в программе может быть много, поэтому лучше их объединить в структуру. Например, мы захотим посчитать 50 число Фибоначчи.

```cpp
#define N 100
typedef struct {
    char a[N];       // number is a[0]*10^0 + a[1]*10^1 + ..+ a[n]*10^n
    unsigned int n;  // наибольшая степень десяти
}Decimal;
```

Напишите функцию **void elong_print(Decimal x)**, которая печатает длинное число и `\n` в конце.

```cpp
int main()
{
    Decimal x = {{7, 4, 1}, 2}; // число 147
    Decimal zero ={{0}, 0};     // число 0 представим как 0 умножить на 10 в степени 0
    
    elong_print(x);     // 147
    elong_print(zero);  // 0
    
    return 0;
}
```

Посылать только реализацию функции `elong_print`.

HEADER
#include <stdio.h>
#include <ctype.h>

#define N 100
struct _Decimal {
    char a[N];       // number is a[0]*10^0 + a[1]*10^1 + ..+ a[n]*10^n
    unsigned int n;  // наибольшая степень десяти
};
typedef struct _Decimal Decimal;

void print (Decimal p);
Decimal set(char str[]);

int main(){
    // struct Decimal d = {{7, 4, 1}, 2};  // number 147
    Decimal d;
    char s[N+1];
    fgets(s, N, stdin);
    d = set(s);
    elong_print(d);
    printf("\n");
    
    return 0;
}

Decimal set(char str[])
{
    int i, j;
    Decimal p;
    for (i=0; isdigit((int)str[i]) ; i++)
        ;
    i--;
    p.n = i;
    for(j=0; i>=0; j++, i--)
        p.a[j] = str[i]-'0';
    for (i=p.n+1; i<N; i++)
        p.a[i] = 0;
    return p;
}
TEST
1234567890
----
1234567890
====
12345678901234567890
----
12345678901234567890
====
37019345927304957203945029374952874307529438759837459827340752304
----
37019345927304957203945029374952874307529438759837459827340752304
====
0
----
0
====
1
----
1
====

## TASKINLINE elong_add Сложение больших чисел

Для хранения больших чисел объявили структуру
```cpp
#define N 100
typedef struct {
    char a[N];       // number is a[0]*10^0 + a[1]*10^1 + ..+ a[n]*10^n
    unsigned int n;  // наибольшая степень десяти
}Decimal;
```

Реализуйте функцию сложения чисел x и y, которая возвращает сумму чисел. Проверьте функцию.

**Decimal add (Decimal x, Decimal y);**

В проверяющую систему посылать только реализацию требуемой функции `add`.

Проверять функцию можно так:
```cpp
int main(){
    Decimal x = {{7, 4, 1}, 2};  // set number 147
    Decimal y = {{3, 1}, 1};     // set number 13
    Decimal res;
    
    res = add(x, y);             // res = x+y = 147+13 = 160
    elong_print(d);              // print 160
    
    return 0;
}
```
HEADER
#include <stdio.h>
#include <ctype.h>

#define N 100
struct _Decimal {
    char a[N];   // number is a[0]*10^0 + a[1]*10^1 + ..+ a[n]*10^n
    unsigned int n;       // наибольшая степень десяти
};
typedef struct _Decimal Decimal;

void print (Decimal p);
Decimal set(char str[]);
Decimal add (Decimal p1, Decimal p2);
void check(Decimal *p);

int main(){
    // struct Decimal d = {{7, 4, 1}, 2};  // number 147
    Decimal a, b, res;
    char s[N+1];

    fgets(s, N, stdin);
    s[N] = 0;
    a = set(s);

    fgets(s, N, stdin);
    s[N] = 0;
    b = set(s); 

    res = add(a,b);
    print(res);
    printf("\n");
    
    check(&res);
    return 0;
}

Decimal set(char str[])
{
    int i, j;
    Decimal p;
    for (i=0; isdigit((int)str[i]) ; i++)
        ;
    i--;
    p.n = i;
    for(j=0; i>=0; j++, i--)
        p.a[j] = str[i]-'0';
//    for(j=p.n+1; j<N; j++)
//        p.a[j] = 0;
    return p;
}
void print (Decimal p)
{
    int i;
    for (i=p.n; i>=0; i--)
        printf("%d", p.a[i]);
}
void check(Decimal * p)
{
    unsigned int i;
    for (i=0; i <= p->n; i++)
        if (p->a[i] > 9) {
            printf("ERROR: a[%d]=%d\n", i, p->a[i]);
        }
}

TEST
1234567890
325
----
1234568215
====
12345678901234567890
12345678901234567890123
----
12358024580135802458013
====
37019345927304957203945029374952874307529438759837459827340752304
87823470523452345723477347583740583274857324875324534538479384595
----
124842816450757302927422376958693457582386763635161994365820136899
====
0
0
----
0
====
1
9
----
10
====
9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999995
1
----
0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000006
====


