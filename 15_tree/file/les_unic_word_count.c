#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define EN_SIZE 26          // сколько букв в латинском алфавите
#define WORD_SIZE 100       // максимальный размер слова
#define hr      printf("-------------------\n")
#define ind(x) ((x)-'a')    // по букве получаем ее порядковый номер
#define alp(x) ((x)+'a')    // по порядковому номеру в массиве получаем букву (ASCII код символа)

struct Node;

typedef struct {
        struct Node * next; // указатель на следующий узел, если нет NULL
        int n;              // в конце слова, сколько раз встретилось это слово
} Letter;

struct Node {
    Letter a[EN_SIZE];
};

/* ***********************************************************************
 * Функции набираемого слова
*/
char word[WORD_SIZE];
int  word_index;            // индекс в массиве первой ПУСТОЙ ячейки

// печатаем слово word[] и счетчик counter
void word_print(int counter)
{
    word[word_index] = '\0';
    printf("%s %d\n", word, counter);
}
// дописываем в конец слова word[] букву с
void word_add_letter(char c)
{
    word[word_index++] = c;
}
// удаляем последнюю букву из word[]
void word_del_letter()
{
    word_index --;
}

/* ***********************************************************************
 * Функции словаря
*/
// печатает все слова из словаря
void dict_print(struct Node * dict)
{
    for(int i = 0; i < EN_SIZE; i++) {
        if (dict->a[i].n) {
            word_add_letter(alp(i));
            word_print(dict->a[i].n);
            word_del_letter();
        }
        if (dict->a[i].next) {
            word_add_letter(alp(i));
            dict_print(dict->a[i].next);
            word_del_letter();
        }
    }
}

// тестируем dict_print
void test_dict_print()
{
    /* ожидаем печати
        car 3
        card 2
        cat 1    
    */
    struct Node c = {}, a = {}, r = {}, d = {};
    c.a[ind('c')].next = &a;
    a.a[ind('a')].next = &r;
    r.a[ind('t')].n = 1;
    r.a[ind('r')].n = 3;
    r.a[ind('r')].next = &d;
    d.a[ind('d')].n = 2;
    
    dict_print(&c);
}    

// выделяет память для нового узла, все расписывает нулями
// возвращает указатель на выделенную память
struct Node * new_node()
{
    return calloc(1, sizeof(struct Node));
}

// добавляет слово str начиная с узла dict
void dict_add_word(struct Node * dict, char * str)
{
    int i = ind(*str);
    if (str[1] == '\0'){
        // если это конец слова, то только увеличиваем счетчик
        dict->a[i].n ++;
    } else {
        // не конец слова
        // если дальше слово не было, делаем следующую букву
        if (dict->a[i].next == NULL)
            dict->a[i].next = new_node();
        // идем на следующую букву слова
        dict_add_word(dict->a[i].next, str+1);
    }
}

// освобождает память для всего дерева
void dict_destroy(struct Node * dict)
{
    for(int i = 0; i < EN_SIZE; i++)
        if (dict->a[i].next != NULL)
            dict_destroy(dict->a[i].next);
    free(dict);
}  

// считает сколько в словаре слов
int dict_count(struct Node * dict)
{
    int counter = 0;
    for(int i = 0; i < EN_SIZE; i++){
        if (dict->a[i].n)
            counter ++;
        if (dict->a[i].next)
            counter += dict_count(dict->a[i].next);
    }
    return counter;
}

// тестируем работу со словарем  
void test_dict()
{
    struct Node * dict = new_node();  // словарь, пока пустой
    hr;
    dict_add_word(dict, "b");
    dict_print(dict);
    /* expect:
    b 1
    */
    assert(dict_count(dict) == 1);
    
    hr;
    dict_add_word(dict, "cat");
    dict_print(dict);
    /* expect:
    b 1
    cat 1
    */
    assert(dict_count(dict) == 2);
    
    hr;
    dict_add_word(dict, "card");
    dict_print(dict);
    /* expect:
    b 1
    card 1
    cat 1
    */
    assert(dict_count(dict) == 3);

    hr;
    dict_add_word(dict, "cat");
    dict_print(dict);
    /* expect:
    b 1
    card 1
    cat 2
    */
    assert(dict_count(dict) == 3);

    dict_destroy(dict);
}

/* *********************************************************
 * функции для чтения и обработки текста (взяли из задачи про частотный словарь)
*/
// возвращает новую строку, в которой остаются только латинские буквы, 
// приведенные к нижнему регистру
char * strip(const char * src)
{
    static char en[27];
    // я не помню алфавит, если его еще нет, сделать алфавит
    if (en[0] == 0) {
        for(int i = 0; 'a' + i <= 'z'; i++)
            en[i] = 'a' + i;
    }
    size_t n = strlen(src);
    char * dst = malloc(1 + n);
    size_t isrc, idst;      // index in src and dst strings
    for(isrc = idst = 0; isrc < n; isrc++) {
        char c = tolower(src[isrc]);
        if (isalpha(c)) {
            dst[idst++] = c;
        }
    }
    dst[idst] = '\0';
    dst = realloc(dst, 1+strlen(dst));
    return dst;
}

// функция для одного теста функции strip
// вызываем strip(s) и сравниваем результат с expected
void test_strip(const char * s, const char * expected)
{
    char * test = strip(s);
    printf("src=%s dst=%s expected=%s\n", s, test, expected);
    assert(strcmp(test, expected) == 0);
    free(test);
}

 
int main()
{
    // test_dict_print();
    // test_dict();
	struct Node * dict = new_node();        // пустой словарь 
	char * s = NULL, *sletters;             // слово и слово после удаления лишних символов
	while(1 == scanf("%ms", &s)) {
		// printf("s=%s, t=%p\n", s, t);
        sletters = strip(s);                // удаляем лишние символы
        
                                            // пропускаем пустую строку
        if (sletters[0] == '\0') {
            free(sletters);
            free(s);
            continue;
        }
		dict_add_word(dict, sletters);
        free(sletters);
        free(s);
	}
    // dict_print(dict);
    
    printf("%d\n", dict_count(dict));
    dict_destroy(dict);
    
    return 0;
}