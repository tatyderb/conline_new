# typedef

lesson = 600085
lang = c

## Создание псевдонимов typedef

Для любого типа можно определить новое имя (псевдоним, user-defined type) с помощью **typedef**:

```cpp
typedef существующий тип псевдоним;
```
Например:
```cpp
typedef unsigned char Age;              // тип для хранения возраста человека в годах
typedef unsigned long long int llu;     // просто надоело писать длинные слова
```
* Использовать псевдоним можно там же, где вы используете тип. 
* Можно использовать как псевдоним, так и исходный тип (но стилистически лучше дальше использовать только псевдоним).
* Псевдоним - одно слово.
* Принято название типа писать с большой буквы (кроме низкоуровневых - `llu` и кроме системных - `size_t`).

```cpp
unsigned char x;
Age student = 17;

llu z = (llu)x * x;
unsigned long long *p = &z; 
```

### Зачем нужны псевдонимы?

Чтобы код был читаемее и его было легко модифицировать.

Пусть в программе хранится возраст в годах и координаты точек на маленьком экранчике. В обоих случаях достаточно типа `unsigned char`.

Вариант 1: в программе НЕ используются псевдонимы.

```cpp
int is_adult(unsigned char student);
void move(unsigned char *x, unsigned char *y, unsigned char dx, unsigned char dy); 
```

Вариант 2: в программе используются псевдонимы.

```cpp
typedef unsigned char Age;
typedef unsigned char Coord;

int is_adult(Age student);
void move(Coord *x, Coord *y, Coord dx, Coord dy); 
```

Представим, что у нас увеличился размер экрана. Для хранения координат теперь нужен тип `unsigned short`. В случае использования `typedef` нужно поменять ровно одну строку (и еще формат при печати и чтении данных). Без `typedef` придется менять во всем коде типы руками, потому что если автоматически везде заменить `unsigned char` на `unsigned short` с помощью поиска и замены в текстовом редакторе, вы сильно увеличите возможную продолжительность жизни.

## QUIZ typedef

Отметьте, где правильно описан псевдоним.

A. `typedef float Temperature;`

B. `typedef int New Balance;`

C. `typedef long double Pressure;`

D. `typedef char int;`

E. `typedef Age unsigned char;`

ANSWER: A,C

## QUIZ использование

`typedef long double Pressure;`

Отметьте синтаксически корректные конструкции

A. `Pressure p = 1031;`

B. `Pressure vacuum(Pressure);`

C. `k = (Pressure)(z + dz);`

ANSWER: A,B,C

## Короче

Многих раздражает в языке Си необходимость писать ключевое слово `struct` при использовании 

```cpp
void move(struct Rect * p, int dx);
``` 
Используйте `typedef` и можно писать короче.

```cpp
struct Point{
    int x;
    int y;
};
typedef struct Point Point;
```
То же самое, но соединим определение структуры с typedef:

```cpp
typedef struct Point {
    int x;
    int y;
} Point;
```

Теперь можно использовать как `struct Point`, так и `Point`:
```cpp
void move(struct Point *p, int dx);
void mirror_x(Point *p);
``` 
Хороший стиль - придерживаться в коде одного способа. Или `struct Point`, или `Point`.

## Анонимные структуры

Можно определять структуры без указания имени. Такие структуры называют **анонимные**. 

Можно определить структуру, переменные и дальше их использовать:

```cpp
struct {
    unsigned char age;
    float weight;
} man, woman, cat;

cat.age = 2;
cat.weight = 4.7;
```
Анонимные структуры не могут быть типом формального аргумента функции:
```cpp
int is_adult(struct p);   // ОШИБКА, не существует тип struct
```
Но если мы используем анонимную структуру и `typedef`, то у нас есть псевдоним типа. Его можно использовать везде, где мы используем тип:
```cpp
typedef struct {
    int hour;
    int minute;
    int second;
} Time;

Time clock = {12, 34, 5};

int time2min(Time t);
Time min2time(int mm);
```

## TASKINLINE 

Определите структуру, описывающую окружность с центром с координатами `x` и `y` типа `int` и радиусом `r` типа `double` так, чтобы было корректен прототип функции:

```cpp
Circle zoom(Circle c, int k);
```
Функцию `zoom` реализовывать НЕ НУЖНО. 

```cpp
ТУТ БУДЕТ ВАШ ПОСЛАННЫЙ КОД

// ---- далее код уже определен в проверяющей системе:
Circle zoom(Circle c, int k);

int main()
{
    Circle c = {1, 2, 3};
    Circle z = zoom(c, 5);
    printf("%.0lf\n", z.r);
    return 0;
}

Circle zoom(Circle c, int k)
{
    Circle res = c;
    res.r *= k;
    return res;
}
```
 
FOOTER
#include <stdio.h>

Circle zoom(Circle c, int k);

int main()
{
    Circle c = {1, 2, 3};
    Circle z = zoom(c, 5);
    printf("%.0lf\n", z.r);
    return 0;
}

Circle zoom(Circle c, int k)
{
    Circle res = c;
    res.r *= k;
    return res;
}
CONFIG
visible_tests:0
score: 5
TEST
1
----
15
====
