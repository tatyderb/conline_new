# Стандартные функции языка С

lesson = 282782

## VIDEO

<iframe width="560" height="315" src="https://www.youtube.com/embed/G0HUky1DRhg" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

## strcpy - копирование строк

Копируют строки с помощью функции **strcpy** (string copy).

```cpp
char *strcpy(char *dest, const char *src);
char *strncpy(char *dest, const char *src, size_t n);
```
* **src** — source (откуда)
* **dest** — destination (куда) — его вернут
* **n** — не более n символов (\0 может не ставить)

Функции `strcpy` и `strncpy` возвращают указатель на результирующую строку `dest`.

Почему первый аргумент `dest`, а второй `src`? По аналогии с выражением `x=5`. Сначала пишем куда копировать значение, потом - какое это значение.

```cpp
char a[100];         // нужно место куда копировать, тут мусор
strcpy(a, "qaz");    // откопировали в массив символы 'q', 'a', 'z', '\0'
printf("%s\n", a);   // qaz
```

<p style="text-align:center">
<img src="https://stepik.org/media/attachments/lesson/276442/strcpy.png" alt="strcpy"/>
</p>

## strncpy

Функция strcpy() копирует строку, на которую указывает src (включая завершающий символ '\0'), в массив, на который указывает dest. Строки не могут перекрываться, и в результирующей строке dest должно быть достаточно места для копии.

Функция strncpy работает аналогично, кроме того, что копируются только первые n байтов строки src. Таким образом, если в n байтах строки src нет нулевого байта, то строка результата **не будет заканчиваться символом '\0'**.

Если длина src меньше, чем n, то остальное место в dest будет заполнено нулями.

<p style="text-align:center">
<img src="https://stepik.org/media/attachments/lesson/276442/strNcpy.png" alt="strncpy"/>
</p>

```cpp
char a [100];			// сами заботимся о месте
strcpy (a, "hello");
printf("%s\n", a);		// hello
strncpy (a, "abc", 2);  // копируем 2 символа, \0 не ставится
printf("%s\n", a);		// abllo 		
a[2] = '\0';            // ставим вручную \0 после откопированных символов
printf("%s\n", a);		// ab
strncpy (a, "abc", 10);	// abc, остальные 6 элементов массива a заполняются нулями
printf("%s\n", a);		// abс
```

## Нельзя копировать в перекрывающийся участок памяти

Реализуем функцию `char * mystrcpy(char *dest, const char *src)` сами, через индексы массивов. С первого символа до '\0' копируем из `src[i]` в `dest[i]`. Не забудем про '\0'.

```cpp
char * mystrcpy1(char *dest, const char *src) {
    int i;
    for (i = 0; src[i] != '\0'; i++)
        dest[i] = src[i];
    dest[i] = '\0';     // так как он в цикле не откопировался, а нужен
    return dest;
}
```

Можно реализовать функцию по-другому: копировать с конца в начало. Сначала вычислим с помощью `strlen`, где '\0', потом будем копировать с '\0' до первого символа строки включительно.

```cpp
char * mystrcpy2(char *dest, const char *src) {
    int i;
    for (i = strlen(src); i >= 0; i--)
        dest[i] = src[i];
    return dest;
}
```

<p style="text-align:center">
<img src="https://stepik.org/media/attachments/lesson/276442/strcpy_overlap.png" alt="strncpy"/>
</p>

Если запустить эти функции на пересекающемся участке из d+2 в d (такая задача возникает часто, например, нужно убрать лидирующие пробелы или нули), то получим из "world" строку "rld" или строку "d", в зависимости от того, какую функцию использовали:
```cpp
char d[100] = "world";
mystrscp1(d, d+2);
printf("%s\n", d);      // rld

strcpy(d, "world");
mystrscp2(d, d+2);
printf("%s\n", d);      // d
```

В стандарте не говорится о том, как именно нужно реализовывать эту функцию. Поэтому поведение не определено. Для копирования перекрывающихся участков памяти есть функция **memmove**, которая копирует из **src** в **dest** через внутренний буффер **n** байт памяти. 

```cpp
void *memmove(void *dest, const void *src, size_t n);
```
```cpp
memmove(d, d+2, strlen(d+2)+1);     // +1 - не забываем копировать \0
```

## strcpy через указатели

Реализуем копирование не через индексы, а через указатели. Указатель s идет по строке src с начала до '\0', сдвигаясь каждый раз на 1 символ. Указатель p идет по строке dest, сдвигаясь каждый раз на 1 символ.

```cpp
char * mystrcpy2(char *dest, const char *src) {
    char * p;
    const char * s;
    for (s = src, p = dest; *s != '\0'; s++, p++)
        *p = *s;
    *p = '\0';     // так как он в цикле не откопировался, а нужен
    return dest;
}
```

* вынесем `s = src, p = dest` в объявление переменных `p` и `s`;
* так как ASCII-код символа '\0' равен 0, то `*s != 0` или тождественно `*s`, так как 0 - ложь, все остальное истина.
* так как результат оператора `=` это значение в правой части (например, значение выражения `x=5` будет 5, то есть истина), то можно внести присвоение `*p = *s` в условие продолжение цикла `*s != 0`,

```cpp
char * mystrcpy2(char *dest, const char *src) {
    char * p = dest;
    const char * s = src;
    for (; *p = *s; s++, p++)
        ;
    *p = *s;     // так как s указывает при выходе из цикла на \0
    return dest;
}
```
* свернем два оператора `*s` и `s++` в один `*s++`. Так как приоритет `++` выше, чем у `*`, то сначала будет срабатывать отложенное увеличение указателя `s++`, а потом прежнее значение указателя будет разыменовано `*s`. Скобки для изменения приоритета не нужны, все работает хорошо.
* заменим for на while

```cpp
char * mystrcpy2(char *dest, const char *src) {
    char * p = dest;
    const char * s = src;
    while (*p++ = *s++)
        ;
    return dest;
}
```
Заметим, что дополнительное копирование '\0' не нужно, так как этот символ сначала откопируется, а потом результат присвоения (ноль) будет проверен на истинность (ложь) и цикл прервется.

## VIDEO

<iframe width="560" height="315" src="https://www.youtube.com/embed/Hlio0zOftWA" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

## strcat - склеить строки

**strcat** - string concatenate - конкатенация (склейка, сложение) строк.

```cpp
char *strcat(char *dest, const char *src);
char *strncat(char *dest, const char *src, size_t n);
```

Функция strcat() добавляет строку str к строке dest, перезаписывая символ '\0' в конце dest и добавляя к строке символ окончания '\0'. Строки не могут перекрываться, а в строке dest должно хватать свободного места для размещения объединенных строк.

Функция strncat() работает аналогичным образом, но добавляет к dest только первые n символов строки src (и **дописывает в конец еще и '\0'** ).

Функции strcat() и strncat() **возвращают указатель на строку**, получившуюся в результате объединения dest.

<p style="text-align:center">
<img src="https://stepik.org/media/attachments/lesson/276442/strcat.png" alt="strcat"/>
</p>

<p style="text-align:center">
<img src="https://stepik.org/media/attachments/lesson/276442/strNcat.png" alt="strncat"/>
</p>

```cpp
#include <stdio.h>
#include <string.h>

int main() {
    char a[100];           // нужно место куда копировать
    char * b;              // сюда будем записывать что вернули функции
    
    strcpy(a, "abc");
    printf("%s\n", a);     // abc
    b = strcat(a, "world");
    printf("%s\n", a);     // abcworld
    printf("%s\n", b);     // abcworld
    
    strcpy(a, "abc");
    strcat(a, "hello");
    printf("%s\n", a);    // abchello
    strncat(a, "xyz", 2); // \0 дописывает
    printf("%s\n", a);    // abchelloxy
    b = strncat(a, "END", 10);
    printf("%s\n", a);    // abchelloxyEND
    printf("%s\n", b);    // abchelloxyEND
    
    return 0;
}
```

Функцию `strcat` легко реализовать в 1 строку кода, используя функции `strcpy` и `strlen`.

## strchr, strrchr - поиск символа в строке

```cpp
char *strchr(const char *s, int c);     // слева направо
char *strrchr(const char *s, int c);    // справа (right) налево
```

* strchr = string + char
* strrchr = string + char + right

Функции возвращают:
* `strchr` - указатель на *первое* вхождение символа **с** в строке **s**.
* `strrchr` - указатель на *последнее* (первое справа) вхождение символа **с** в строке **s**.
* **NULL** - если символа **с** в строке **s** нет.

```cpp
char * a = "Hello, world!";
char * p1 = strchr (a, 'l');
char * p2 = strrchr (a, 'l'); 
printf("%s\n", p1);			// llo, world!
printf("%s\n", p2);			// ld!
```

### Принадлежит ли символ алфавиту

```cpp
const char * s = "({[<";        // алфавит
int c = getchar();              // символ
char * p = strchr(s, c);        // указатель на символ в алфавите

if (p != NULL)                  // символ в алфавите?
    printf("Символ %с открывающая скобка\n", c);
```

### Извлечь из пути имя файла

```cpp
char * path = "/home/student/hello.c";  // путь
char * file = strrchr(path, '/');       // file указывает на последний / или NULL
if (file)                               // если не NULL,
	file ++;                            // то указывать на следующий за / символ
printf("filename is %s\n", file);       // filename is hello.c
```

## strstr - поиск подстроки в строке

```cpp
char *strstr(const char *str, const char *substr);
```

Функция strstr() ищет первое вхождение подстроки substr в строке str. Завершающий символ `\0' не сравнивается.

Возвращает указатель на начало подстроки, или NULL, если подстрока не найдена.

```cpp
char * text = "I have a dog. I have a bomb. I have a cat";
if (NULL != strstr(text, "bomb"))
    printf("WAAA! BOMB!!!!\n");
```

## strtok - разбор строки по токенам (словам)

Вызвается несколько раз и разбирает строку **s** по токенам. Токен - это последовательность символов НЕ разделителей. Вы уже встречались с понятием токена в `scanf("%s", s)`, когда видели, что читается последовательность символов до пробельного символа. Это не слово в понятии русского или английского языка, это *токен* - "слово" в символах заданного алфавита разделителей **delim**.

*   разбивает строку на подстроки по разделителю из алфавита **delim**;
*   модифицирует строку **s**, записывая **\0** в места, где находятся разделители из **delim**;
*   возвращает указатель на очередную подстроку после каждой модификации;
*   для каждого последующего вызова, кроме первого, указываем **NULL** вместо **s**;
*   последний раз (нет больше delim) вернет **NULL**.

```cpp
char s[] = "a,bb; cccc?dd";         // текст
const char * delim = ",;?!. \t";    // алфавит разделителей
for (char * p = strtok(s, delim);   // начинаем разбор, передаем строку s 
		p != NULL;                  // пока не нашли новый разделитель
		p = strtok (NULL, delim) )  // в следующий раз вызываем от NULL
	printf("%s\n", p);              // вместо разделителя \0, поэтому можно напечатать токен от p до \0
```
получим:
```cpp
a
bb
ccc
dd
```

## Это все?

Есть другие функции для работы со строками. Для справки вызовите команду `man 3 string`, чтобы получить обзор функций из файла `string.h`:

```cpp
man 3 string
NAME
stpcpy,  strcasecmp,  strcat,  strchr,  strcmp,  strcoll,  strcpy,  strcspn,  strdup, strfry, strlen, strncat,
strncmp, strncpy, strncasecmp, strpbrk, strrchr, strsep, strspn, strstr,  strtok,  strxfrm,  index,  rindex  -
string operations
```

