#include <stdio.h>
#include <string.h>
#include <assert.h>

void replace(char * dst, const char * src);

int main()
{
    char d[1000];
    
    replace(d, "abcbomb lord bomb xyz");
    printf("<%s>\n", d);
    assert(0 == strcmp(d, "abcwatermelon lord bomb xyz"));
    
    return 0;
}

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
