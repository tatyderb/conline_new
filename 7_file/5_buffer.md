# Функции ввода-вывода

lesson = 

## Аналоги printf и scanf

Существуют функции, аналогичные `printf` и `scanf`, но работающие с любыми потоками или строками, а не столько со stdout и stdin.

```cpp
 #include <stdio.h>

int printf(const char *format, ...);
int fprintf(FILE *stream, const char *format, ...);
int dprintf(int fd, const char *format, ...);
int sprintf(char *str, const char *format, ...);
int snprintf(char *str, size_t size, const char *format, ...);
```

`printf("hello")` это `fprintf(stdout, "hello");

Посмотрим, как в имени функции кодируется, куда собираемся писать:

| *Функция* | *Аргумент КУДА* | *куда* |
|---|---|---|
| printf |  нет | `stdout` |
| <b>f</b>printf | `FILE * stream` | поток |
| <b>d</b>printf | `int fd` | файловый дескриптор |
| <b>s</b>printf | `char * str` | строка |
| <b>sn</b>printf | `char * str, size_t size` | строка с контролем переполнения |

И по тому же принципу построен набор функций, аналогичных scanf:

```cpp
int scanf(const char *format, ...);
int fscanf(FILE *stream, const char *format, ...);
int sscanf(const char *str, const char *format, ...);
```

## Специфичные функции

Функции семейства printf и scanf универсальные. Они понимают что и как им нужно читать и писать, разбирая форматную строку.

Существуют узкоспециализированные функции чтения и записи символа и строки.

```cpp
#include <stdio.h>

int fputc(int c, FILE *stream);
int putc(int c, FILE *stream);
int putchar(int c);

int fputs(const char *s, FILE *stream);
int puts(const char *s);
```

| *Функция* | *Что делает* |
|---|------|
| fputc | записывает символ *c*, преобразованный к `unsigned char` в *stream* |
| putc | то же, что fputc, но может быть макросом |
| putchar | `putc(c, stdout)` |
| fputs | записывает строку *s* и '\n' в *stream* |
| puts | `fputs(s, stdout)` |

Для ввода:

```cpp
#include <stdio.h>

int fgetc(FILE *stream);
int getc(FILE *stream);
int getchar(void);
int ungetc(int c, FILE *stream);

char *fgets(char *s, int size, FILE *stream);
char *gets(char *s);
```

| *Функция* | *Что делает* |
|---|------|
| fgetc | читает символ *c*, преобразованный из `unsigned char` к `int` в *stream* |
| getc | то же, что fgetc, но может быть макросом |
| getchar | `getc(c, stdin)` |
| ungetc | возвращает обратно в поток *stream* символ *c* |
| fgets | читает строку длиной не более *size*-1 символов из *stream* и записывает ее в *s* |
| gets | не используйте эту функцию |

Старайтесь не использовать `ungetc`. Эта функция не предназначена для многопоточной программы.

Почему не рекомендуется использовать *gets* ? Потому что вы не контролируете длину введённых данных и может возникнуть переполнение строки *s*.

## Почему int?

Почему fgetc возвращает int, а не unsigned char?

## Буферизация


