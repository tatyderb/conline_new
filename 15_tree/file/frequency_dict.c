#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

typedef struct {
        const char * s;
        unsigned int n;
} Data;

struct Node {
    Data val;            // данные в узле
    struct Node * left;  // левый ребенок
    struct Node * right; // правый ребенок
};

struct Node * tree_add(struct Node * t, const char * s);
void tree_print(struct Node * tree);
void tree_destroy(struct Node * tree);
int tree_count(struct Node * t);        // сколько узлов в дереве t
void tree_to_arr(struct Node * t, Data * arr, int * pi);

// функция сравнения для qsort массива из структур Data
int cmp_Data(const void * p1, const void * p2)
{
    const Data * d1 = p1;
    const Data * d2 = p2;
    unsigned n1 = d1->n;
    unsigned n2 = d2->n;
    if (n1 != n2)
        return (n1 < n2) - (n1 > n2);
    return strcmp(d1->s, d2->s);
}

// печать массива arr размера n
void arr_print(Data * arr, int n) {
    // printf("----------------------------------\n");
    for(int i = 0; i < n; i++)
        printf("%s %d\n", arr[i].s, arr[i].n);
}

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
    /*
    // сначала проверим, что strip работает нормально
    test_strip("abc", "abc");
    test_strip("12abc", "abc");
    test_strip("abc34", "abc");
    test_strip("12a55bc34", "abc");
    test_strip("13452345234./,567456", "");
    return 0;
    */
    
	struct Node * t = NULL;                 // дерево   
	char * s = NULL, *sletters;             // слово и слово после удаления лишних символов
	while(1 == scanf("%ms", &s)) {
		//printf("s=%s, t=%p\n", s, t);
        sletters = strip(s);                // удаляем лишние символы
        
                                            // пропускаем пустую строку
        if (sletters[0] == '\0') {
            free(sletters);
            free(s);
            continue;
        }
		t = tree_add(t, sletters);
		//tree_print(t);
		//printf("\n");
        free(sletters);
        free(s);
	}
	// tree_print(t);
	// printf("\n");
    
    int count = tree_count(t);                  // сколько узлов в дереве?
    Data * arr = malloc(count * sizeof(Data));  // массив для хранения всех узлов
    int i = 0;
    tree_to_arr(t, arr, &i);                    // записываем в массив копии данных в каждом узле
    // arr_print(arr, count);
    qsort(arr, count, sizeof(Data), cmp_Data);  // сортируем массив
    arr_print(arr, count);                      // печатаем отсортированные данные

    free(arr);                                  // освобождаем память
	tree_destroy(t);
	return 0;
}

struct Node * tree_add(struct Node * t, const char * s)
{
	if (t==NULL) {
		t = malloc(sizeof(struct Node));
		t->val.s = strdup(s);
        t->val.n = 1;
		t->left = NULL; 
		t->right = NULL;
		return t;
	}
    int cmp = strcmp(s, t->val.s);
	if (cmp < 0)
		t->left = tree_add(t->left, s);
	else if (cmp > 0)
		t->right = tree_add(t->right, s);
    else {
        t->val.n ++;
    }
	return t;	// x == t->val
}

void tree_print(struct Node * t)
{
	if (t == NULL)
		return;
	tree_print(t->left);
    printf("%s %d\n", t->val.s, t->val.n);
	tree_print(t->right);
}

// возвращает сколько узлов в дереве t
int tree_count(struct Node * t)
{
	if (t == NULL)
		return 0;
	return tree_count(t->right) + tree_count(t->left) + 1;
}

// копирует данные из узлов дерева t в массив arr начиная с индекса i, всего count узлов
void tree_to_arr(struct Node * t, Data * arr, int * pi)
{
    if (t == NULL)
        return;
    tree_to_arr(t->left, arr, pi);
    arr[*pi] = t->val;
    (*pi)++;
    tree_to_arr(t->right, arr, pi);    
}    

void tree_destroy(struct Node * tree)
{
	if (tree == NULL)
		return;
	tree_destroy(tree->left);
	tree_destroy(tree->right);
    free((char*)(tree->val.s));
	free(tree);
}
