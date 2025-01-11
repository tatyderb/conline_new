# Задачи на структуры

lesson = 596771
lang = c

## TASKINLINE time_struct 12-часовой циферблат

Ручные часы имеют **12 часовой** циферблат (от 00:00 до 11:59).

Для хранения и представления показаний часов используется структура:

```cpp
typedef struct{ 
	int h; // часы 
	int min; // минуты (от 0 до 59)
}TicTac;
```

Написать следующие функции для работы с часами:

```cpp
// получает показание часов a и возвращает показание этих часов 
// через min минут, .
TicTac after(TicTac a, int min);

// "переводит" вперед стрелки этих часов (me) 
// на a.h часов и a.min минут 
void forward(TicTac * me, TicTac a);

// "переводит" назад стрелки этих часов (me) 
// на a.h часов и a.min минут 
void backward(TicTac * me, TicTac a);

// проверяет совпадают ли показания часов a и b
// если совпадают, возвращает 1, если нет - 0
int isEqualTime(TicTac a, TicTac b);

// печатает показания этих часов в формате hh:mm\n
void printTic(TicTac a);
```
Посылать только реализации нужных функций. Если вы пишете дополнительные функции, например, `time2min` и `min2time`, то посылать все дополнительные функции.

Объявление структуры и функцию `main` посылать не нужно. Они уже есть в проверяющей системе.

Для проверки функций используется код:
```cpp
int main(){
    TicTac a,b,c;
    int mk;
    
    scanf("%d:%d", &(a.h), &(a.min));
    scanf("%d", &mk);
    scanf("%d:%d", &(b.h), &(b.min));
    
    printf("equal: %d\n",isEqualTime(a,b));
    c = after(a, mk);
    printf("after: ");
    printTic(c);
    
    c = a;
    printf("forward: ");
    forward(&a, b);
    printTic(a);
    
    printf("backward: ");
    backward(&c, b);
    printTic(c);
    
    return 0;
}
```

HEADER
#include <stdio.h>
#include <stdlib.h>
#define WEEK 10080
typedef struct{
	int h;
	int min;
}TicTac;

TicTac after(TicTac a, int min);
void forward(TicTac * me, TicTac a);
void backward(TicTac * me, TicTac a);
void printTic(TicTac a);
int isEqualTime(TicTac a, TicTac b);

int main(){
    TicTac a,b,c;
    int mk;
    
    scanf("%d:%d", &(a.h), &(a.min));
    scanf("%d", &mk);
    scanf("%d:%d", &(b.h), &(b.min));
    
    printf("equal: %d\n",isEqualTime(a,b));
    c = after(a, mk);
    printf("after: ");
    printTic(c);
    
    c = a;
    printf("forward: ");
    forward(&a, b);
    printTic(a);
    
    printf("backward: ");
    backward(&c, b);
    printTic(c);
    
    return 0;
}

TEST
02:10 25 02:10
----
equal: 1
after: 02:35
forward: 04:20
backward: 00:00
====
02:00 55 02:55
----
equal: 0
after: 02:55
forward: 04:55
backward: 11:05
====
11:50 43 0:17
----
equal: 0
after: 00:33
forward: 00:07
backward: 11:33
====
9:22 240 6:00
----
equal: 0
after: 01:22
forward: 03:22
backward: 03:22
====

## TASKINLINE struct_line_0rotR Поворот

Написать функцию 
```cpp
void rotRLine(struct Line * t);
```
Она поворачивает отрезок на плоскости XY **на 90 градусов по часовой стрелке вокруг точки (0,0)**.

Напечатайте полученный отрезок и его длину с точностью до 3 десятичных знаков.

**Посылать на проверку всю программу.**

Входные данные: 4 целых числа через пробел - x, y координаты точки - целые числа через пробел.

Выходные данные: x y координаты концов отрезка и его длина с точностью до десятичных знаков.

```cpp
typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point a;    // начало отрезка
    Point b;    // конец отрезка
    float len;  // длина отрезка
} Line;

float distance(Point a, Point b);   // расстояние между точками
void scanLine(Line * t);
void printLine(Line t);
void rotRLine(Line * t);

int main() {
    Line t;
    
    scanLine(&t);
    // тут должен быть вызов функции rotRLine
    printLine(t);
    
    return 0;
}
```
CODE
typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point a;    // начало отрезка
    Point b;    // конец отрезка
    float len;  // длина отрезка
} Line;

float distance(Point a, Point b);   // расстояние между точками
void scanLine(Line * t);
void printLine(Line t);
void rotRLine(Line * t);

int main() {
    Line t;
    
    scanLine(&t);
    // тут должен быть вызов функции rotRLine
    printLine(t);
    
    return 0;
}

TEST
3 0 0 4
---
0 -3 4 0 5.000
====
0 4 3 0
---
4 0 0 -3 5.000
====
0 1 0 5
---
1 0 5 0 4.000
====
1 2 3 4
----
2 -1 4 -3 2.828
====

## TASKINLINE struct_colors Цвета RGB

**В языке Си числа печатаются и читаются в  шестнадцатеричной системе счисления по формату %X или %x, в десятичной системе счисления по формату %d**

```cpp
unsigned int k = 255;
printf("%X\n", k);      // FF - большими буквами
printf("%x\n", k);      // ff - маленькими буквами
printf("%u\n", k);      // 255, unsigned int
printf("%d\n", 255);    // 255, int
```

Для описания цветов при отображении на мониторе существуют разные форматы.

Один из форматов **RGB**: все цвета получаются смешением красного (red), зеленого (green) и синего (blue) различной интенсивности. Интенсивность можно описать структурой:
```cpp
typedef struct
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
} Color;
```
Эти же цвета используются в "HTML"-формате. В этом случае цвет представляется шестизначным шестнадцатеричными числами, записанными в символьном виде. Старшие разряды соответствуют числу "red" RGB-формата, следующие два - "green", младшие - "blue". Число записывается в переменные типа

```cpp
unsigned long long
```
Например, если в формате Color
```cpp
red = 255; green = 128; blue = 22;
```
то в HTML-формате будет записано
```cpp
FF8016
```
Требуется написать функции:
```cpp
// считать RGB-формат с консоли
Color getColor();
// перевод из RGB-формата в число
unsigned long long convertToHTML(Color);
// преобразование числа цвета в RGB-формат
Color convertToRGB(unsigned long long);
// печать цвета в RGB-формате (печать значений в десятичном виде через пробел)
// red green blue: 
// 255 128 222
// Печатать только числа через пробел и \n в конце!!!
void printRGB(Color);

// печать цвета в HTML-формате и \n в конце. 
// Примеры: FFA902 0AA3FF
void printHTML(Color);
```
Отправлять только функции.

Функции будут проверяться так:
```cpp
int main(){
    Color z, z2;
    unsigned long long html;
    
    z = getColor();
    printRGB(z);
    
    html = convertToHTML(z);
    printf("%llu\n", html);
    printHTML(z);
    
    z2 = convertToRGB(html);
    printRGB(z2);
    
    return 0;
}
```
HEADER
#include <stdio.h>
typedef struct
{
	unsigned char red, green, blue;
}Color;

void printRGB(Color);

Color getColor();

unsigned long long convertToHTML(Color);

void printHTML(Color);

Color convertToRGB(unsigned long long );

int main(){
    Color z, z2;
    unsigned long long html;
    
    z = getColor();
    printRGB(z);
    
    html = convertToHTML(z);
    printf("%llu\n", html);
    printHTML(z);
    
    z2 = convertToRGB(html);
    printRGB(z2);
    
    return 0;
}

TEST
255 128 16
----
255 128 16
16744464
FF8010
255 128 16
====
255 255 255
----
255 255 255
16777215
FFFFFF
255 255 255
====
0 200 200
----
0 200 200
51400
00C8C8
0 200 200
====
115 115 254
----
115 115 254
7566334
7373FE
115 115 254
====

## rusDelRest Деление с остатком

Тут будет задача про русское деление с остатком. Но не сегодня.



