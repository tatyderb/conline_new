# Задачи на строки

lesson = 640234
lang = c_valgrind

## Задачи

Постарайтесь при решении задач максимально использовать стандартные функции языка Си.

Не изобретайте велосипед.

## TASKINLINE str_4 strcat

Напишите функцию. Посылать только функцию!
```cpp
char * my_strcat (char *dest, const char *src);
```
которая работает так же, как [стандартная функция](https://stepik.org/lesson/282782/step/7) языка С
```cpp
char *strcat(char *dest, const char *src)
```
* **Нельзя** использовать функцию `strcat`,
* можно использовать другие стандартные функции работы со строками, например `strlen` и `strcpy`.

Функция main в проверяющей системе уже написана, она печатает строки до и после вызова функций. Её посылать не нужно.

CODE
char * my_strcat (char *dest, const char *src)
{
    // здесь нужно написать код
}    
HEADER
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 256

char *my_strcat(char *dest, const char *src);

char * strip(char * s) {
    char * p;
    p = s;
    p = strrchr(p, ']');
    // if (p==NULL || s[0]!='[') {
    if (p==NULL ) {
        printf("Wrong test string (%s) , expected [ and ] bracketes.\n", s);
        exit(1);
    }
    *p = '\0';
    return s+1;
}

int main()
{
    char * p, *pd, *dst;
    char s[N];
    char d[N];
    char e[N];
    
    fgets(d, N, stdin);
    dst = strip(d);
    fgets(s, N, stdin);
    p = strip(s);
    memcpy(e, d, N);
    
	printf("before src=[%s]\n", p);
	printf("before dst=[%s]\n", dst);
    pd = my_strcat(dst, p);
    strcat(e+1, p);
	printf("dst   =[%s]\n", dst);	
	printf("expect=[%s]\n", e+1);	
	printf("return=[%s]\n", pd);	
    
	printf("after src =[%s]\n", p);	
	return 0;
}
#define strcat return
#line 10001
TEST
[Hel]
[lo]
----
before src=[lo]
before dst=[Hel]
dst   =[Hello]
expect=[Hello]
return=[Hello]
after src =[lo]
====
[abc]
[Hello]
----
before src=[Hello]
before dst=[abc]
dst   =[abcHello]
expect=[abcHello]
return=[abcHello]
after src =[Hello]
====
[Hello, world!      The end. ]
[I'll be back.]
----
before src=[I'll be back.]
before dst=[Hello, world!      The end. ]
dst   =[Hello, world!      The end. I'll be back.]
expect=[Hello, world!      The end. I'll be back.]
return=[Hello, world!      The end. I'll be back.]
after src =[I'll be back.]
====
[]
[]
----
before src=[]
before dst=[]
dst   =[]
expect=[]
return=[]
after src =[]
====
[a]
[b]
----
before src=[b]
before dst=[a]
dst   =[ab]
expect=[ab]
return=[ab]
after src =[b]
====
[]
[Hello]
----
before src=[Hello]
before dst=[]
dst   =[Hello]
expect=[Hello]
return=[Hello]
after src =[Hello]
====
[q]
[]
----
before src=[]
before dst=[q]
dst   =[q]
expect=[q]
return=[q]
after src =[]
====

## TASKINLINE str_len Самое длинное слово

Напечатать самое длинное слово и его длину. Если несколько слов одинаковой длины, то печатайте первое из них.

В этой и следующих задачах можно считать, что в строке будет не более 1000 символов.

TEST
a high explosive bomb is one 
that employs a process called detonation 
to rapidly release its chemical energy
---
detonation 10
====
the simplest and oldest type of bombs store energy
in the form of a low explosive
---
explosive 9
====
mumbai also known as bombay is 
the capital city of the indian state of maharashtra
---
maharashtra 11
====
the seven islands that came to constitute 
mumbai were home to communities of fishing colonies
---
communities 11
====
bomb bomb bomb
---
bomb 4
====
BOMB
---
BOMB 4
====

## TASKINLINE str_bomb1 Слово bomb

Напечатать `YES`, если в тексте есть СЛОВО **bomb**. Иначе напечатать `NO`.

TEST
a high explosive bomb is one 
that employs a process called detonation 
to rapidly release its chemical energy
---
YES
====
the simplest and oldest type of bombs store energy
in the form of a low explosive
---
NO
====
mumbai also known as bombay is 
the capital city of the indian state of maharashtra
---
NO
====
the seven islands that came to constitute 
mumbai were home to communities of fishing colonies
---
NO
====
bomb bomb bomb
---
YES
====
BOMB
---
NO
====

## TASKINLINE str_bomb2 Часть слова bomb

Напечатать `YES`, если в тексте есть ПОДСТРОКА **bomb**. Иначе напечатать `NO`.

TEST
i have a bomb.
---
YES
====
dog and cat
The simplest and oldest type of bombs 
store energy in the form of a low explosive.
---
YES
====
Mumbai (also known as Bombay) is the capital city of the Indian state of Maharashtra. 
---
NO
====
The seven islands that came to constitute 
Mumbai were home to communities of fishing colonies
---
NO
====
bomb? bomb! bomb!!!
---
YES
====
BOMB
---
NO
====

## TASKINLINE str_bomb3 Часть слова bomb без учета регистра

Напечатать `YES`, если в тексте есть ПОДСТРОКА **bomb**  (без учта регистра, то есть находить слова BOMB, bOmB и так далее). Иначе напечатать `NO`.

Подсказка: напишите функцию, которая делает все буквы строки маленькими:
```cpp
char * stringtolower(char * s); 
```
и для каждого символа строки `s` выполняет код
```cpp
s[i] = tolower(s[i]);
```

TEST
i have a bomb.
---
YES
====
The simplest and oldest type of bombs 
store energy in the form of a low explosive.
---
YES
====
Mumbai (also known as Bombay) is the capital city of the Indian state of Maharashtra. 
---
YES
====
The seven islands that came to constitute 
Mumbai were home to communities of fishing colonies
---
NO
====
bomb? bomb! bomb!!!
---
YES
====
BOMB
---
YES
====

## TASKINLINE str_bomb4 Сколько бомб?

Напечатать сколько раз в тексте встретилась подстрока **bomb** (маленькими буквами).

TEST
i have a bomb. you have a bomb.
---
2
====
The simplest and oldest type of bombs 
store energy in the form of a low explosive.
---
1
====
Mumbai (also known as Bombay) is the capital city of the Indian state of Maharashtra. 
---
0
====
The seven islands that came to constitute 
Mumbai were home to communities of fishing colonies
---
0
====
bomb? bomb! bomb!!!
---
3
====
BOMB
---
0
====
bombandbomb and cat
dog, bambino and bombino.
----
3
====



