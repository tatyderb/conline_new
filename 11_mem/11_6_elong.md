# Длинная арифметика

lesson = 308217
lang = c_valgrind

## SKIP video

тут видео полосы

## Большие числа

Вспомним, как мы работали с большими числами, которые больше, чем самый большой целочисленный тип.

Число 147 это $7 \cdot 10^0 + 4 \cdot 10^1 + 1 \cdot 10^2$. 

Можно представить любое число $a$ как 
 $a_0 \cdot 10^0 + a_1 \cdot 10^1 + a_2 \cdot 10^2$
 
 Будем хранить коэффициенты $a_0$, $a_1$, $a_2$ в массиве `a` как `a[0]`, `a[1]`, `a[2]`. И будем в `n` хранить максимальную степень 10 в разложении числа по степеням 10.

Объединим массив `a` и поле `n` в структуру `Decimal`, так как они описывают одно и то же число. Чисел в программе может быть много, поэтому лучше их объединить в структуру. Например, мы захотим посчитать 50 число Фибоначчи.

![Decimal](https://stepik.org/media/attachments/lesson/308217/elong_arr.png)

```cpp
#define N 100
typedef struct {
    char a[N];       // number is a[0]*10^0 + a[1]*10^1 + ..+ a[n]*10^n
    unsigned int n;  // наибольшая степень десяти
}Decimal;
```

Числа можно задавать сразу при объявлении переменных:
```cpp
Decimal x = {{7, 4, 1}, 2};     // число 147
Decimal zero = {{0}, 0};        // число 0
```
В числе 147 количество цифр 3, максимальная степень 10 будет 2. В поле `n` храним 2. Можно хранить количество цифр, но мы договорились, что в нашей реализации функции печати мы ожидаем именно максимальную степень 10.

Мы написали функции [elong_print](https://stepik.org/lesson/607327/step/3) и [elong_add](https://stepik.org/lesson/607327/step/4) для печати числа и сложения двух чисел. [elong_set](https://stepik.org/lesson/275922/step/9) преобразовывала строку в длинное число.

`void elong_print(Decimal x);` - передается *копия* структуры со всем массивом, очень тяжелый вызов функции.

Лучше передавать указатель на такую "тяжелую" структуру `void elong_print(Decimal * px);` 

Аналогично, можно написать функции преобразования из int в Decimal. Это опять передача копии большого массива из функции:
```cpp
Decimal elong_set_int(unsigned int x); 
// использование:     
// Decimal x = elong_set_int(147);
```
Лучше написать функцию так, чтобы передавать только указатель на структуру:
```cpp
void elong_set_int(Decimal * dst, unsigned int x);      
// использование:     
// Decimal x;
// elong_set_int(&x, 147);  заполняем переменную х значениями для числа 147
```

## Добавим динамическую память

При фиксированном размере массива у нас не использовалась память, если числа были короткие и мы все равно были ограничены числом $10^{100}-1$

![Decimal](https://stepik.org/media/attachments/lesson/308217/elong_arr.png)

Если в структуре хранить вместо массива указатель на динамический массив, то мы сэкономим память и уберем ограничение сверху на длину в 100 цифр.

```cpp
typedef struct {
    char * a;        // number is a[0]*10^0 + a[1]*10^1 + ..+ a[n]*10^n
    unsigned int n;  // наибольшая степень десяти
}Decimal;
```
Количество цифр в массиве `n+1`. Но при реализации функций `elong_set_int` или умножения, не хочется **много раз** увеличивать размер динамически выделенной памяти на +1 `char`. Разумнее было бы сразу выделить много байт, если не хватит, то выделить больше, а если не все использовалось, то выделить меньше. Поэтому введем в структуру поле **size** - сколько выделено памяти (в количестве элементов массива `a`).

```cpp
typedef struct {
    char * a;        // number is a[0]*10^0 + a[1]*10^1 + ..+ a[n]*10^n
    unsigned int n;  // наибольшая степень десяти
    size_t  size;    // размер массива a
}Decimal;
```
![size](https://stepik.org/media/attachments/lesson/308217/elong_arr2.png)

По картинке напишем код:
```cpp
Decimal x;
x.n = 2;
x.size = 8;
x.a = malloc(x.size);
x.a[0] = 7;
x.a[1] = 4;
x.a[2] = 1;

Decimal * px = &x;
```
Разумно написать функцию, которая выполнит те же действия:
```cpp
Decimal x;              // выделена память под переменную х (фиолетовый прямоугольник)
elong_set_int(&x, 147); // внутри вызывается минимум 1 malloc (желтый массив с цифрами)  
```
Реализация функции:
```cpp
void elong_set_int(Decimal * px, unsigned int number)
{
    if (number == 0){       // 0*10**0
        px->size = 1;
        px->n = 0;
        px->a = malloc(px->size);
        px->a[0] = 0;
        return;
    }

    // number точно меньше 10 в 100, выделим память с запасом
    px->size = 100;
    px->a = malloc(px->size);
    
    
    for(px->n = 0; number > 0; px->n++){
        px->a[px->n] = number % 10;
        number /= 10;
    }
    px->n --;
    
    // выделим памяти точно под хранение числа
    px->size = px->n + 1;
    px->a = realloc(px->a, px->size);
}
```

Сразу же напишем функцию, которая освобождает память
```cpp
void elong_destroy(Decimal * px)
{
    free(px->a);        // освобождаем желтый массив с цифрами
}
```
Проверка кода (запускаем с valgrind):
```cpp
int main()
{
    Decimal x;
    elong_set_int(&x, 147);
    elong_print(&x);
    elong_check(&x);
    elong_destroy(&x);
    
    elong_set_int(&x, 654321);
    elong_print(&x);
    elong_check(&x);
    elong_destroy(&x);
    
    elong_set_int(&x, 7);
    elong_print(&x);
    elong_check(&x);
    elong_destroy(&x);
    
    elong_set_int(&x, 0);
    elong_print(&x);
    elong_check(&x);
    elong_destroy(&x);
    
    return 0;
}
```

Функция [elong_print](https://stepik.org/lesson/607327/step/3?unit=602468) аналогична той, что вы писали для длинного числа фиксированной длины.

Функция `elong_check` проверяет, что во всех значащих ячейках массива лежат числа от 0 до 9 включительно. Рекомендуем реализовать эти функции самостоятельно и запустить пример.

## TASKINLINE elong_add2 Сложение чисел

Для хранения больших чисел объявили структуру

```cpp
typedef struct {
    char * a;           // number is a[0]*10^0 + a[1]*10^1 + ..+ a[n]*10^n
    unsigned int n;     // наибольшая степень десяти
    unsigned int size;  // размер выделенной динамической памяти в а
}Decimal;
```

Ноль должен быть представлен как $0 \cdot 10^0$

Реализуйте функцию сложения чисел a и b, которая возвращает сумму чисел.

`void` **elong_add** `(const Decimal * a, const Decimal * b, Decimal * res);`

В проверяющую систему посылать только реализацию требуемой функции. Номера строк вашего кода начинаются с 100001.

Для проверки функции используется код:
```cpp
int main(){
    Decimal a;  
    Decimal b;  
    Decimal res;
    
    elong_set_int(&a, 147);    // 147
    elong_set_int(&b, 13);     // 13
    
    elong_add(&a, &b, &res);   // res = a+b = 147+13 = 160
    
    elong_print(res);          // print 160

    elong_destroy(&a);
    elong_destroy(&b);
    elong_destroy(&res);
    
    return 0;
}
```

HEADER
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct _Decimal {
    char * a;       // number is a[0]*10^0 + a[1]*10^1 + ..+ a[n]*10^n
    unsigned int n;       // наибольшая степень десяти
    unsigned int size;
};
typedef struct _Decimal Decimal;

void print (Decimal * p);
Decimal set(const char * str);
void elong_add (const Decimal * a, const Decimal * b, Decimal * res);
void elong_destroy(Decimal * p);
void check(Decimal *p);

int main(){
    // struct Decimal d = {{7, 4, 1}, 2};  // number 147
    Decimal a, b, res;
    char * s = NULL;
    size_t n = 0;
    getline(&s, &n, stdin);
    a = set(s);
    getline(&s, &n, stdin);
    b = set(s);
    free(s);
    
    elong_add(&a, &b, &res);
    
    print(&res);
    printf("\n");
    check(&res);
    
    elong_destroy(&a);
    elong_destroy(&b);
    elong_destroy(&res);
   
    return 0;
}
void elong_destroy(Decimal * p){
    free(p->a);
}
Decimal set(const char * str)
{
    int i, j;
    Decimal a;
    Decimal * p = &a;
    for (i=0; isdigit((int)str[i]) ; i++)
        ;
    i--;
    if (i < 0){
        fprintf(stderr, "Error data [%s], n=%d\n", str, i);
    }
    p->n = i;
    p->size = p->n+1;
    p->a = malloc((size_t)(p->size * sizeof(char)));
    for(j=0; i>=0; j++, i--)
        p->a[j] = str[i]-'0';
    // for (j=p->n+1; j<N; j++)
	// p->a[j] = 0;
    return a;
}
void print (Decimal * p)
{
    int i;
    for (i=p->n; i>=0; i--)
        printf("%d", p->a[i]);
}
void check(Decimal * p)
{
    int i;
    for (i=0; i <= p->n; i++)
        if (p->a[i] > 9 || p->a[i] < 0) {
            printf("ERROR: a[%d]=%d\n", i, p->a[i]);
        }
}
#line 100001

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
5999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
1
----
6000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
====

## `Decimal * elong_set_int(unsigned int number)`

Можно написать функцию `elong_set_int` так, чтобы она принимала один аргумент - число и возвращала **указатель** на структуру. Тогда и `elong_add` стоит переписать в похожем стиле. Использование:
```cpp
Decimal * a = elong_set_int(147);
Decimal * b = elong_set_int(13);
Decimal * res = elong_add(a, b);
elong_print(res);
```

В случае структуры `Decimal` выигрыш небольшой. Но для структуры, которая описывает работу с файлами `FILE`, выигрыш заметный, ибо в структуре около 100 полей. Поэтому функция открытия файла `FILE * fopen(const char * path, const char * mode);`

Функция должна вернуть `px`, который указывает на структуру. Нельзя вернуть из функции указатель на локальную в этой функции переменную. Эта переменная после выхода из функции будет "разрушена". Можно вернуть указатель на выделенную динамическую память и вне функции, потом её использовать и в конце концов освободить.

![Decimal](https://stepik.org/media/attachments/lesson/308217/elong_arr2.png)

В функции `elong_set_int` объявлена переменная `px`. Её значение вернем из функции. То есть к выделению памяти для массива данных (желтого) добавится ещё одно выделение памяти для структуры ("большой ящик", фиолетовый прямоугольник).

Реализация функции:
```cpp
Decimal * elong_set_int(unsigned int number)
{
    // сначала выделим память под саму структуру (фиолетовый прямоугольник)
    Decimal * px = malloc(sizeof(Decimal));
    
    if (number == 0){       // 0*10**0
        px->size = 1;
        px->n = 0;
        px->a = malloc(px->size);
        px->a[0] = 0;
        return px;
    }

    // number точно меньше 10 в 100, выделим память с запасом
    px->size = 100;
    px->a = malloc(px->size);
    
    
    for(px->n = 0; number > 0; px->n++){
        px->a[px->n] = number % 10;
        number /= 10;
    }
    px->n --;
    
    // выделим памяти точно под хранение числа
    px->size = px->n + 1;
    px->a = realloc(px->a, px->size);
    return px;
}
```

Сразу же напишем функцию, которая освобождает память, заметим, освобождаем память в обратном порядке.
```cpp
void elong_destroy(Decimal * px)
{
    free(px->a);        // освобождаем желтый массив с цифрами
    free(px);           // освобождаем фиолетовый прямогольник, саму структуру
}
```
Проверка кода (запускаем с valgrind):
```cpp
int main()
{
    Decimal * x;
    x = elong_set_int(147);
    elong_print(x);
    elong_check(x);
    elong_destroy(x);
    
    x = elong_set_int(654321);
    elong_print(x);
    elong_check(x);
    elong_destroy(x);
    
    x = elong_set_int(7);
    elong_print(x);
    elong_check(x);
    elong_destroy(x);
    
    x = elong_set_int(0);
    elong_print(x);
    elong_check(x);
    elong_destroy(x);
    
    return 0;
}
```

## TASKINLINE elong_add3 Сложение чисел

Для хранения больших чисел объявили структуру

```cpp
typedef struct {
    char * a;           // number is a[0]*10^0 + a[1]*10^1 + ..+ a[n]*10^n
    unsigned int n;     // наибольшая степень десяти
    unsigned int size;  // размер выделенной динамической памяти в а
}Decimal;
```

Ноль должен быть представлен как $0 \cdot 10^0$

Реализуйте функцию сложения чисел a и b, которая возвращает сумму чисел.

`Decimal *` **elong_add** `(const Decimal * a, const Decimal * b);`

В проверяющую систему посылать только реализацию требуемой функции.
```cpp
int main(){
    Decimal * a;  
    Decimal * b;  
    Decimal * res;
    
    a = elong_set_int(147);    // 147
    b = elong_set_int(13);     // 13
    
    res = elong_add(a, b);     // res = a+b = 147+13 = 160
    
    elong_print(res);          // print 160
    
    elong_destroy(a);
    elong_destroy(b);
    elong_destroy(res);
   
    return 0;
}
```

HEADER
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct _Decimal {
    char * a;       // number is a[0]*10^0 + a[1]*10^1 + ..+ a[n]*10^n
    unsigned int n;       // наибольшая степень десяти
    unsigned int size;
};
typedef struct _Decimal Decimal;

void print (Decimal * p);
Decimal * set(const char * str);
Decimal *elong_add (const Decimal * a, const Decimal * b);
void elong_destroy(Decimal * p);
void check(Decimal *p);

int main(){
    // struct Decimal d = {{7, 4, 1}, 2};  // number 147
    Decimal *a, *b, * res;
    char * s = NULL;
    size_t n = 0;
    getline(&s, &n, stdin);
    a = set(s);
    getline(&s, &n, stdin);
    b = set(s);
    free(s);
    
    res = elong_add(a, b);
    print(res);
    printf("\n");
    check(res);
    
    elong_destroy(a);
    elong_destroy(b);
    elong_destroy(res);
   
    return 0;
}
void elong_destroy(Decimal * p){
    free(p->a);
    free(p);
    p = NULL;
}
Decimal * set(const char * str)
{
    int i, j;
    Decimal * p = (Decimal *)malloc(sizeof(Decimal));
    for (i=0; isdigit((int)str[i]) ; i++)
        ;
    i--;
    if (i < 0){
        fprintf(stderr, "Error data [%s], n=%d\n", str, i);
    }
    p->n = i;
    p->size = p->n+1;
    p->a = (char *)malloc((size_t)(p->size * sizeof(char)));
    for(j=0; i>=0; j++, i--)
        p->a[j] = str[i]-'0';
    // for (j=p->n+1; j<N; j++)
	// p->a[j] = 0;
    return p;
}
void print (Decimal * p)
{
    int i;
    for (i=p->n; i>=0; i--)
        printf("%d", p->a[i]);
}
void check(Decimal * p)
{
    int i;
    for (i=0; i <= p->n; i++)
        if (p->a[i] > 9 || p->a[i] < 0) {
            printf("ERROR: a[%d]=%d\n", i, p->a[i]);
        }
}
#line 100001
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
5999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
1
----
6000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
====

## TASKINLINE toLongN Длинные числа по основанию 100

Реализовывать длинную арифметику можно по-разному. Например, можно хранить числа в строках.

Не обязательно использовать основание 10. Это удобно для человека, но очень неэкономно по памяти. В 1 байте хранятся числа от 0 до 9, для них хватит 4 бит. Экономнее хранить числа по основанию 256, но такую задачу тяжело отлаживать студентам. Решим компромиссную задачу.

* возьмем основание 100,
* добавим хранение знака числа (положительные и отрицательные числа),
* в поле `n` будем хранить количество ячеек с данными.

Дана строка цифр длинной не более 200 символов. В начале строки может стоять не цифровой символ: "+" или "-". Если строка начинается с цифры или символа "+" - это положительное число. Если строка начинается с символа "-" - число отрицательное.

Для хранения и представления числа используется структура:

```cpp
typedef struct{
	char *dig;	// массив для хранения числа:
                // a[0] * 100^0 + a[1] * 100^1 + .. + a[n - 1] * 100^(n-1)
	int n; 		// размер числа в разрядах
	char sign;	// знак числа
} LongN;
```

* Число записывается по основанию 100. При этом младшие разряды числа записываются в начало массива, а старшие - в конец.

* Для положительных чисел и нуля, знак **sign** записывается как 0, для отрицательных - как 1.

* Размер числа **n** записывается как количество разрядов числа по основанию 100. Например, для числа 12345, n=3;

Написать функцию `LongN getLongN(char * s)`, которая преобразует данную строку в длинное число.

Пример использования функции:
```cpp
LongN x = getLongN("123456789012345");
```

Посылать в проверяющую систему только реализацию требуемой функции.

Советуем для отладки все же написать функцию main, функции печати и освобождения памяти. Их посылать не нужно. Они нужны только для отладки функции `getLongN`.

HEADER
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct{
	char *dig;
	char sign;
	int n;
}LongN;

LongN getLongN(char * s);

void showDigit(LongN a){
	int i;
	if (a.sign)
		printf("- ");
	else
		printf("+ ");
	for( i = a.n - 1 ; i > -1; i--){
		printf("%d ", a.dig[i]);
	}
	printf("\n");
};

void destroy(LongN a){
	free(a.dig);
};

int main(){
  LongN a;
	char s[201];
	scanf("%s", s);
	a = getLongN(s);
	showDigit(a);
	destroy (a);
	return 0;
}

#line 1000001

TEST
-12345
----
- 1 23 45
====
+1234
----
+ 12 34
====
0
----
+ 0
====
1234000000000000000000000000000000000009
----
+ 12 34 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 9
====
-12340000000000000000000000000000000000015
----
- 1 23 40 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 15
====
