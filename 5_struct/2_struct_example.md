# Примеры использования структур

lesson = 596770

## Пример: Отрезок на оси Х

Опишем структуру для хранения одномерного отрезка по оси Х `[start, finish]`. И определим отрезки **a** `[-4, 7]` и **b** `[6, 0]`. Объявим еще один отрезок **m** и введем его начало и конец с клавиатуры.

**Объявление нового типа лучше указывать в начале файла, после директив препроцессора**.

```cpp
#include <stdio.h>

// объявили новый тип данных struct Segment
// 1D отрезок
struct Segment {
    int start;    // один конец отрезка
    int finish;   // другой конец отрезка
};

int main()
{
    struct Segment a = {-4, 7}, b;
    b.start = 6;
    b.finish = 0;
    
                            // распечатаем эти отрезки:
    printf("a = [%d, %d]\n", a.start, a.finish);
    printf("b = [%d, %d]\n", b.start, b.finish);
    
    struct Segment m;
    scanf("%d", &m.start);  // читаем 
    scanf("%d", &m.start);
                            // печатаем
    printf("m = [%d, %d]\n", m.start, m.finish);
}
```

## Пример: Когда приедет электричка?

[time.c](https://stepik.org/media/attachments/lesson/596769/time.c) - вся программа.

Напишем функции, которые переводят время в часах и минутах в минуты с 0:00, а потом обратно. Определим структуру `Time` с полями `h` (часы) и `m` (минуты).

Напишем функции работы со структурой и решим задачу, во сколько прибудет электричка, которая отправилась в h1:m1 и ехала dh:dm? В зависимости от циферблата можем получить разное "во сколько" (для 24-часового или для 12-часового циферблата). Напишем решение для 24-часового циферблата.

*Я бы все времена держала в минутах с 0:00, и преобразовывала к часам и минутам только в момент печати. Но у нас учебная задача и мы покажем как хранить промежуточные значения в часах и минутах.*

### Объявление структуры

Объявим новый тип `struct Time`
```cpp
struct Time {
    int h;      // часы
    int m;      // минуты
};
```

### Объявление переменных в main

Проверим работу на случае, когда электричка выехала в 22:55, ехала 2:07 и приехала в 1:02.

В main объявим и проинициализиуем переменные:
```cpp
    struct Time t1 = {22, 55};
    struct Time dt = { 2, 7};
    struct Time t2,                     // результат
                expected_res = {1, 2};  // ожидаемый результат для тестов
```

### Печать времени

Сначала будем писать как используем функции, потом их реализовывать. Это поможет понять, какие аргументы нужны и какой будет тип возвращаемого значения.

Для печати времени в main объявленных переменных напишем:
```cpp
    print_time(t1);     // 22:55
    print_time(dt);     // 02:07
```
* имя функции print_time
* аргумент один, тип такой же, как у `t1` или `dt`, то есть `struct Time`,
* ничего не возвращает, то есть `void`.

Получился прототип:
```cpp
void print_time(struct Time t);
```
В функцию передаем *время* и печатаем его:
```cpp
// печать hh:mm
void print_time(struct Time t)
{
    printf("%02d:%02d\n", t.h, t.m);
}
```
В функции у нас **единственная** переменная **t** - аргумент. Нет никаких "переменных h и  m". Есть `t.h` - поле `h` переменной `t` и `t.m` - поле `m` переменной `t`.

*Скомплируем и запустим программу. Проверим, что функция реализована правильно.*

### time2min h, m -> mm

Напишем функцию `time2min`, она получает *время* и возвращает минуты с 0:00. Действуем по шаблону: объявили переменную `res` того типа, что должна вернуть функция, записали в нее данные, вернули `res`:
```cpp
int time2min(struct Time t)
{
    int res;
    res = t.h * 60 + t.m;
    return res;
}
```
В функцию передана переменная `t` время, у нее есть поля `h` часы и `m` минуты.

Вызываем в main и сразу проверяем ее работу:
```cpp
    int mm = time2min(dt);  // 2:07
    assert(mm == 127);
```

В функцию передали "большую сумку с данными" (`struct Time`), вернули из функции `int`. Аналогично в `min2time` из одного числа сделаем "большую сумку с данными" :

### min2time

В функции `min2time` действуем по тому же шаблону объявить/вычислить/вернуть. Но возвращаемое значение *время*, то есть `struct Time`:

```cpp
// mm -> h, m
struct Time min2time(int mm)
{
    struct Time res;    // объявили res типа struct Time
    res.m = mm %60;     // вычислили значение res
    res.h = mm/60 % 24;
    return res;         // вернули res
}
```
Вызываем в main:
```cpp
    struct Time t = min2time(127);  
    print_time(t);                  // 02:07
```

### структура == структура

Хочется написать assert, но для структур **оператор == не работает**, нужно написать функцию сравнения. Сравниваем у 2 структур каждое поле. Пусть вернет 1, если все поля одинаковые и 0, если разные.
```cpp
int is_equal(struct Time t1, struct Time t2)
{
    if (t1.h != t2.h)
        return 0;
    if (t1.m != t2.m)
        return 0;
    return 1;
}
```
используем ее в assert:
```cpp
    assert(1==is_equal(min2time(127), dt));
```

Вызов `assert` и функцию можно написать короче, подробнее расскажем на следующем уроке. Если вы уже знаете логические операторы в других языках, то оператор AND в Си это **&&**:
```cpp
int is_equal(struct Time t1, struct Time t2)
{
    return t1.h == t2.h && t1.m == t2.m;
}    
```
и вызов 
```cpp
    assert(is_equal(min2time(127), dt));
```

### add - сложение времен

Функция `add` получает *время* и *время*, возвращает тоже *время*.
```cpp
// t1 + t2
struct Time add(struct Time t1, struct Time t2)
{
    int mmres = time2min(t1) + time2min(t2);    // всего минут с 0:00
    struct Time res = min2time(mmres);          // из минут во время
    return res;                                 // вернули время
}
```

Протестируем функции:
```cpp
int main()
{
    struct Time t1 = {22, 55};
    struct Time dt = { 2, 7};
    struct Time t2,
                expected_res = {1, 2};
    
    print_time(t1);
    print_time(dt);
    
    t2 = add(t1, dt);
    print_time(t2);
    
    assert(1==is_equal(t2, exp_t2));
    
    return 0;
}
```
Вся программа единым куском:
```cpp
#include <stdio.h>

// Объявляем новый тип данных struct Time:
struct Time {
    int h;      // часы
    int m;      // минуты
};

void print_time(struct Time t);     // печать hh:mm

int time2min(struct Time t);        // h, m -> mm
struct Time min2time(int mm);       // mm -> h, m
struct Time add(struct Time t1, struct Time t2);    // t1 + t2

int main()
{
    struct Time t1 = {22, 55};
    struct Time dt = { 2, 7};
    struct Time t2,
                expected_res = {1, 2};
    
    print_time(t1);
    print_time(dt);
    
    t2 = add(t1, dt);
    print_time(t2);
    
    return 0;
}

// печать hh:mm
void print_time(struct Time t)
{
    printf("%02d:%02d\n", t.h, t.m);
}

// h, m -> mm
int time2min(struct Time t)
{
    int res;
    res = t.h * 60 + t.m;
    return res;
}

// mm -> h, m
struct Time min2time(int mm)
{
    struct Time res;
    res.m = mm %60;
    res.h = mm/60 % 24;
    return res;
}

// t1 + t2
struct Time add(struct Time t1, struct Time t2)
{
    int mmres = time2min(t1) + time2min(t2);
    struct Time res = min2time(mmres);
    return res;
}    
```

## Пример (повторение). Читаем число

Целое число можно прочитать с клавиатуры в отдельной функции. 

```cpp
int read_int();
void scan_int();
```
Реализация и вызов функций:
```cpp
int read_int()
{
    int res;
    scanf("%d", &res);
    return res;
}
void scan_int(int * p)
{
    scanf("%d", p);     // p уже указатель, не нужно &
}
int main()
{
    int x, y;
    x = read_int();
    scan_int(&y);
    printf("x=%d y=%d\n", x, y);
    
    return 0;
}
```

## Пример. Читаем время

Аналогично можно прочитать не целое число, а струтуру (много данных)

Время можно прочитать с клавиатуры с помощью `scanf` в отдельной функции.
```cpp
void printTime(struct Time t)
{
    printf("%02d:%02d\n", t.h, t.m);
}
struct Time read_Time()
{
    struct Time res;
    scanf("%d:%d", &res.h, &res.m);
    return res;
}
void scan_Time(struct Time * p)
{
    scanf("%d:%d", &p->h, &p->m);     // УКАЗАТЕЛЬ на поле h, нужно &
}
int main()
{
    struct Time t1, t2;
    t1 = read_Time();
    scan_Time(&t2);
    
    printTime(t1);
    printTime(t2);
    
    return 0;
}
```

## Пример. Отрезок на плоскости XY

[line.c](https://stepik.org/media/attachments/lesson/596770/line.c)

Отрезок задается двумя точками. Сначала определим структуру и функции для работы с точками.

Точка на плоскости XY имеет (пусть целые) координаты х и y.
```cpp
typedef struct {
    int x;
    int y;
} Point;
```

### Печать точки

Будем печатать точку по формату `(x,y) `, в конце пробел.

```cpp
void printPoint(Point p)
{
    printf("(%d,%d) ", p.x, p.y);
}
```
Объявим в main переменные (точки) и распечатаем их:
```cpp
    Point p1 = {4, 3};
    Point p2 = {-4, -3};
    printPoint(p1);     // (4,3)
    printPoint(p2);     // (-4,-3)
```

### Расстояние между 2 точками

Для вычисления расстояния между двумя точками напишем функцию `distance`. Проверим ее работу в main:
```cpp
    float d = distance(p1, p2);
    assert(d == 10);
```
Реализация функции:
```cpp
float distance(Point p1, Point p2)
{
    int dx = p1.x - p2.x;
    int dy = p1.y - p2.y;
    return sqrt(dx*dx + dy*dy);
}
```

### Сдвиг точки на dx

* Можно при сдвиге **создавать новую точку**, как в `movePoint1`. 
* Можно **изменять существующую точку**, как в `movePoint2`.

Использование функций:
```cpp
    // из точки p (4,3) сделаем новую точку p_new (6,3)
    Point p_new = movePoint1(p1, 2);     // 6, 3
    printPoint(p_new);
    Point exp_point = {6, 3};
    
    // существующую точку p_new сдвинем еще раз, получим (8,3)
    movePoint2(&p_new, 2);
    printPoint(p_new);                  // 8, 3
```

Берем **копию** точки, **возвращаем новую** точку:
```cpp
// Получаем новую точку на dx от p.
Point movePoint1(Point p, int dx)
{
    Point res = p;      // новая точка res из старой p
    res.x += dx;
    return res;         // вернули (откопировали значение) новой точки
}
```

Берем **адрес** точки и по этому адресу **изменяем значение**:
```cpp
void movePoint2(Point * p, int dx)
{
    p->x += dx;
}
```

### Сравнение структур

Чтобы использовать assert, напишем проверку на равенство точек:
```cpp
int is_equal(Point p1, Point p2)
{
    return p1.x == p2.x && p1.y == p2.y;
}
```
Определим, какие данные ожидаем получить и сравним с ними результаты сдвига:
```cpp
    Point p_new = movePoint1(p1, 2);    // 6, 3
    printPoint(p_new);
    Point exp_point = {6, 3};           // ожидаемый результат (6,3)
    assert(is_equal(exp_point, p_new));
    
    exp_point.x += 2;                   // ожидаемый результат (8,3)
    movePoint2(&p_new, 2);
    printPoint(p_new);                  // 8, 3
    assert(is_equal(exp_point, p_new));
```

### Прочитать точку с клавиатуры

Как в `move`, есть два варианта - создать точку и заполнить значения в уже существующей:
```cpp
    Point p1, p2;
    p1 = readPoint();   // возвращаем новую точку
    scanPoint(&t2);     // заполняем значения полей уже существующей
    
    printPoint(p1);
    printPoint(p2);
```
Возвращаем новую точку:
```cpp
Point readPoint()
{
    Point res;
    scanf("%d%d", &res.x, &res.y);
    return res;
```
Изменяем уже существующую:
```cpp
void scanPoint(Point * p)
{
    int x, y;
    scanf("%d%d", &x, &y);
    p->x = x;
    p->y = y;
    // или короче scanf("%d%d", &p->x, &p->y);
}
```

## Line - отрезок `[a,b]`

Отрезок определяется двумя точками. Объявим структуру `Line` для описания отрезка `[a,b]`:
```cpp
typedef struct{
    Point a;
    Point b;
} Line;    
```
Выделим в main код, который тестирует поведение `Point` в отдельную функцию `testPoint`, а в `main` начнем тестировать функции отрезка.

```cpp
    Line s = {{2, 3}, {5, 7}};
    printLine(s);
```

### printLine - печать отрезка 

Реализуем функцию `printLine`. Можно написать так:
```cpp
void printLine(Line s)
{
    printf("(%d,%d) (%d,%d) \n", s.a.x, s.a.y, s.b.x, s.b.y);
}
```
или так:
```cpp
void printLine(Line s)
{
    printPoint(s.a);
    printPoint(s.b);
    printf("\n");
}
```
Выберите какой вариант вам нравится больше. Попытайтесь понять почему.

### length - длина отрезка

Напишем тест для функции `length`. Она вычисляет длину отрезка. 

Сначала напишем тест:
```cpp
    Line s = {{2, 3}, {5, 7}};
    printf("length=%.2f\n", length(s));
    assert(length(s) == 5);
```
Длина - это расстояние между концами отрезка. Расстояние между точками вычисляет функция `distance`:
```cpp
float length(Line p1)
{
    return distance(p1.a, p1.b);
}
```