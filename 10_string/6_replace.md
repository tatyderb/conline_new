# replace

lesson = 341699
lang = c_valgrind

## Постановка задачи

Дана строка. Нужно заменить первое вхождение подстроки "bomb" на "watermelon". Исходная строка должна остаться прежней. Напишем функцию замены из строки `src` в строку `dst`:

```cpp
void replace(char * dst, const char * src);
```

Использование функции:

```cpp
int main()
{
    char d[1000];
    
    replace(d, "abcbomb lord bomb xyz");
    printf("<%s>\n", d);
    assert(0 == strcmp(d, "abcwatermelon lord bomb xyz"));
    
    return 0;
}
```

## Способ 1. 

Будем собирать новую строку `dst` из старой строки `src`. Объявим переменные:

* Указатели:
    * **s** - адрес начала строки с бомбой, сначала `s = src`
    * **p** - адрес начала бомбы или NULL, если бомбы нет,
    * **d** - куда копировать очередную часть строки, сначала `d = dst`

Пусть в строке будет хотя бы одна бомба.

1. найдем где бомба, **p = strstr(s, "bomb");** - `p` указывает на начало бомбы
2. скопируем текст до бомбы, (если строка начиналась с адреса 100, а бомба с адреса 103, то между ними 3 = 103 - 100 символа, `n = p - s`, где `n` - сколько символов до бомбы)
3. передвинем указатель `d` в конец этого текста, `d = d + n`
4. допишем "watermelon",
5. передвинем указатель `d` в конец этого текста,
6. поставим указатель `s` за бомбу,
7. скопируем оставшуюся строку от `s` до конца в `d`

Если бомбы в строке нет, то после п.1 копируем сразу всю строку из `s` в `d`.

![replace.png](https://stepik.org/media/attachments/lesson/341699/replace.png)

Переведем алгоритм на язык Си:
```cpp
void replace(char * dst, const char * src)
{
    size_t lenbomb = strlen("bomb");
    size_t lenwater = strlen("watermelon");
    
    char * s;   // src: указатель на начало подстроки, где ищем bomb
    char * p;   // src: указатель на начало bomb
    char * d;   // dst: указатель на конец уже скопированной части
    
    // сначала
    s = (char *)src;            // ищем во всей строке src
    p = NULL;                   // про бомбу ничего не известно
    d = dst;                    // еще ничего не скопировали
    
    // ищем бомбу начиная с адреса s
    p = strstr(s, "bomb");      // p указывает на начало бомбы или NULL
    
    // обезвредим бомбу
    if (p != NULL) {            // бомба есть
        size_t n = p - s;       // количество символов перед бомбой
        strncpy(d, s, n);       // скопируем символы перед бомбой в dst
        d = d + n;              // передвинем d в конце строки
        strcpy(d, "watermelon");// допишем в конец строки арбуз
        d = d + lenwater;       // передвинем конец строки за арбуз
        
        s = p + lenbomb;        // указатель на остаток строки поставим за бомбой
    }
    
    // оставшаяся строка
    strcpy(d, s);
}
```
Этот алгоритм очень неудобно отлаживать с помощью отладочной печати, ибо в строке `dst` может не оказаться в конце `\0`. Для отладки рекомендуем сначала написать в массив `dst` все 0, а потом, когда алгоритм заработает с valgrind, положить в массив гарантированный мусор и убедиться, что в `dst` в конце концов поставлен `\0`.

Сначала отладим с 0 во всех ячейках:
```cpp
    char d[1000] = {};
```
При дальнейшей отладке напишем туда "мусор" (строку большей длины, например, такую):
```cpp
    char d[1000] = "012345678901234567890123456789012345678901234567890123456789";
```

## Способ 1.2. Вместо strcpy используем strcat

![replace.png](https://stepik.org/media/attachments/lesson/341699/replace.png)

Можно упросить код алгоритма, копируя в `dst` текст не `strncpy` и `strcpy`, а использовать `strncat` и `strcat`. Тогда не придется контролировать движение указателя `d` и на каждом этапе можно напечатать строку `dst`, у нее всегда будет `\0`.

Нужно только гарантировать, что `dst` это `""`, то есть в начале строки `dst` лежит `\0`: 

```cpp
void replace(char * dst, const char * src)
{
    size_t lenbomb = strlen("bomb");
    
    char * s;   // src: указатель на начало подстроки, где ищем bomb
    char * p;   // src: указатель на начало bomb
    
    // сначала
    s = (char *)src;            // ищем во всей строке src
    dst[0] = '\0';              // без этого strcat работать не будет
    
    // ищем бомбу начиная с адреса s
    p = strstr(s, "bomb");      // p указывает на начало бомбы или NULL
    
    // обезвредим бомбу
    if (p != NULL) {            // бомба есть
        size_t n = p - s;       // количество символов перед бомбой
        strncat(dst, s, n);     // скопируем символы перед бомбой в dst
        strcat(dst, "watermelon");// допишем в конец строки арбуз
        
        s = p + lenbomb;        // указатель на остаток строки поставим за бомбой
    }
    
    // оставшаяся строка
    strcat(dst, s);
}
```
Этот алгоритм проще написать, но работает не так эффективно, как предыдущий.

## Способ 1.3. Не вычисляем n

Можно избавиться от вычисления длины строки до бомбы (меньше кода - меньше ошибок).

Поставим `\0` вместо первого `b` в бомбе и `s` будет указывать на строку `"abc"`, которую можно скопировать или strcpy, или strcat.

![replace_cat.png](https://stepik.org/media/attachments/lesson/341699/replace_cat.png)

Нельзя изменять исходную строку `src`. Сделаем динамическую копию и будем "портить" копию. Не забудьте в конце освободить память.

```cpp
void replace(char * dst, const char * src_original)
{
    // сделаем копию строки src_original, выделив память динамически
    char * src = srcdup(src_original);

    size_t lenbomb = strlen("bomb");
    
    char * s;   // src: указатель на начало подстроки, где ищем bomb
    char * p;   // src: указатель на начало bomb
    
    // сначала
    s = (char *)src;            // ищем во всей строке src
    dst[0] = '\0';              // без этого strcat работать не будет
    
    // ищем бомбу начиная с адреса s
    p = strstr(s, "bomb");      // p указывает на начало бомбы или NULL
    
    // обезвредим бомбу
    if (p != NULL) {            // бомба есть
        *p = '\0';              // вместо 'b' ставим '\0'
        strcat(dst, s);         // скопируем символы перед бомбой в dst
        strcat(dst, "watermelon");// допишем в конец строки арбуз
        
        s = p + lenbomb;        // указатель на остаток строки поставим за бомбой
    }
    
    // оставшаяся строка
    strcat(dst, s);
    
    // в конце нужно освободить память, в которой лежит копия строки
    free(src);
}
```

## Замена в той же строке

Напишем алгоритм, который заменяет "bomb" на "watermelon" в той же строке. Функция будет иметь один аргумент:
```cpp
void replace(char * src);
```
Использование:
```cpp
int main()
{
    char d[1000] = "abcbomb lord bomb xyz";
    
    replace(d);
    printf("<%s>\n", d);
    assert(0 == strcmp(d, "abcwatermelon lord bomb xyz"));
    
    return 0;
}
```
* Длины:
    * `size_t lenbomb = strlen("bomb");`
    * `size_t lenwater = strlen("watermelon");`
* Указатели:
    * **p** - адрес начала бомбы или NULL, если бомбы нет,

* Найдем адрес начала бомбы,
* сдвинем текст после бомбы так, чтобы на место бомбы влез арбуз, так как это перекрывающиеся участки памяти, то `strcpy` использовать нельзя, только [memmove](https://stepik.org/lesson/618366/step/3?unit=613844)
* на место бомбы напишем арбуз, нельзя копировать `\0`, то есть нельзя использовать `strcpy`, только `strncpy` или `memcpy`. Используем второе для единообразия.

```cpp
void replace(char * src)
{
    size_t lenbomb = strlen("bomb");        // длина бомбы    
    size_t lenwater = strlen("watermelon"); // длина арбуза
    
    char * p = strstr(src, "bomb");
    if (p == NULL)
        return;
    memmove(p + len_bomb, p + lenwater, strlen(p + lenbomb));
    memcpy(p, "watermelon");
}
```

## TASKINLINE str_bomb5 Заменим все бомбы

Напечатать текст, заменив **все** подстроки `bomb` на `watermelon`.

Напишите эффективный код. Если заменили одну `bomb`, то не надо начинать поиск бомб с начала строки.

TEST
i have a bomb.
---
i have a watermelon.
====
i have a bomb. you have a bomb.
---
i have a watermelon. you have a watermelon.
====
Mumbai (also known as Bombay) is the capital city of the Indian state of Maharashtra. 
---
Mumbai (also known as Bombay) is the capital city of the Indian state of Maharashtra. 
====
The seven islands that came to constitute 
Mumbai were home to communities of fishing colonies
---
The seven islands that came to constitute 
Mumbai were home to communities of fishing colonies
====
bomb? bomb! bomb!!!
---
watermelon? watermelon! watermelon!!!
====
BOMB
---
BOMB
====
