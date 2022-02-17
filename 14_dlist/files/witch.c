#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node;

typedef struct {
    char rank;      // достоинство карты
    char suit;      // масть карты
} Card;

typedef struct {
    char * name;
    struct Node * hand;
} Gamer;


typedef void * Data;

// *********************************** Double linked list API
struct Node {
	struct Node * next;
	struct Node * prev;
	Data data;
};

void list_init(struct Node * list);

void list_insert(struct Node * list, struct Node * t);
void list_insert_before(struct Node * list, struct Node * t);
void list_remove(struct Node * t);

struct Node * list_push_front(struct Node * list, Data d);
struct Node * list_push_back(struct Node * list, Data d);

Data list_pop_front(struct Node * list);
Data list_pop_back(struct Node * list);
Data list_delete(struct Node * t);

void list_print (struct Node * list);
int list_is_empty(struct Node * list);

void list_clear(struct Node * list);
void list_destroy(struct Node * list);

// создаем и уничтожаем список
struct Node * list_create()
{
    struct Node * list = malloc(sizeof(struct Node));
    list_init(list);
    return list;
}
void list_init(struct Node * list)
{
	list->next = list->prev = list;
}
void list_destroy(struct Node * list)
{
    list_clear(list);
    free(list);
}

int  list_is_empty(struct Node * list)
{
	return list->next == list;
}
void list_insert(struct Node * list, struct Node * t)
// insert t after element list
{
	t->next = list->next;
	t->prev = list;
	list->next->prev = t;
	list->next = t;
}
void list_insert_before(struct Node * list, struct Node * t)
// insert t before element list
{
	list_insert(list->prev, t);
}
void list_remove(struct Node * list)
{
	struct Node * p = list->prev;
	p->next = list->next;
	list->next->prev = p;
}
void list_remove(struct Node * list)
{
	struct Node * p = list->prev;
	p->next = list->next;
	list->next->prev = p;
}
struct Node * list_remove_front(struct Node * list)
{
	struct Node * p = list->next;
    list_remove(p);
    return p;
}
struct Node * list_remove_back(struct Node * list)
{
	struct Node * p = list->prev;
    list_remove(p);
    return p;
}
void list_foreach(struct Node * list, void (*func)(Data d, void * param), 
		void * param)
{
	struct Node * p;
	for(p = list->next; p != list; p = p->next)
		func(p->data, param);
}
// list_foreach(list, print_it, stderr);
/*
void print_it(Data d, void * param)
{
	FILE * fd = param;
	fprintf(fd, "%d ", d);
}
*/
struct Node * list_push_front(struct Node * list, Data d)
// return newly inserted node
{
	struct Node * p = malloc(sizeof(struct Node));
	p->data = d;
	list_insert(list, p);
	return p;
}
struct Node * list_push_back(struct Node * list, Data d)
// return newly inserted node
{
	struct Node * p = malloc(sizeof(struct Node));
	p->data = d;
	list_insert_before(list, p);
	return p;
}
Data list_pop_front(struct Node * list)
// remove list head, return its data
{
	return list_delete(list->next);
}
Data list_pop_back(struct Node * list)
// remove list tail, return its data
{
	return list_delete(list->prev);
}

Data list_delete(struct Node * p)
// return newly inserted node
{
	list_remove(p);
	Data d = p->data;
	free(p);
	return d;
}
/*
void list_print(struct Node * list)
{
	list_foreach(list, print_it, stdout);
	printf("\n");
}
void sum_it(Data d, void * param)
{
	*(int*)param += d;
}
Data list_sum(struct Node * list)
{
	Data sum = 0;
	list_foreach(list, sum_it, &sum);
	return sum;
}
*/
void list_clear(struct Node * list)
{
    while(!list_is_empty(list))
        list_delete(list->next);
}
void list_next(struct Node * list, struct Node * p)
{
    p = p->next;
    if (p == list)
        p = p->next;
    return p;
}
ine list_is_one(struct Node * list)
{
    return list->next == list->prev && list->next != list;
}
// **************************************************** Card API
void print_card(Card card)
{
    printf("%c%c", card.rank, card.suit);
}
void print_it(Card card, void * param)
{
    print_card(card);
}
void hand_print(struct Node * list)
{
	list_foreach(list, print_it, stdout);
	printf("\n");
}

int valid_card(Card card)
{
    char * const suit = "cshd";
    char * const rank = "23456789TJQKA";
    return strchr(suit, card.suit) && strchr(rank, card.rank);
}
Card * card(struct Node * p)
{
    return p->data;
}    
void drop_pairs(struct Node * hand)
{
    struct Node * p;    // для какой карты начинаем искать пару
    struct Node * t;    // эта карта сравнивается на пару к p
    for(p = hand->next; p != hand; ) {
        // printf("Find pair to %c%c\n", p->card()->rank, p->card()->suit);
        if (p->card()->rank == 'Q' && p->card()->suit == 's') {   // дама пик, ее не сбрасываем
            p = p->next;
            continue;
        }
        else if (p->card()->rank == 'Q') {                     // дама НЕ пик, сбрасываем одну
            t = p;
            p = p->next;
            printf("drop %c%c: ", t->card()->rank, t->card()->suit);
            list_delete(t);
            hand_print(hand);
            continue;
        }
        
        struct Node * pnext = p->next; // если не сбросили карты, надо передвинуть p на следующую карту
        for(t = p->next; t != hand; t = t->next) {
            if (p->card()->rank == t->card()->rank) {
                printf("drop %c%c %c%c: ", p->card()->rank, p->card()->suit, t->card()->rank, t->card()->suit);
                
                pnext = p->next;
                // пара стоит рядом, перепрыгнем через неё
                if (pnext == t)
                    pnext = t->next;
                list_delete(p);
                list_delete(t);
                hand_print(hand);
                break;
            }    
        }
        // надо передвинуть p на следующую карту
        p = pnext;
    }
}    

#define MAX_GAMERS 6
int main()
{
    // struct Node list[MAX_GAMERS];
    // struct Node * hand[MAX_GAMERS]; // hand[i] = &list[i];
    
    char * line;
    scanf("%ms", &line);
    
    int n;  // количество игроков сейчас
    scanf("%d", &n);
    // printf("n = %d\n", n);
    if (n < 2 || n > 6) {
        fprintf(stderr, "Number of gamers should be between 2 and %d, now %d\n", MAX_GAMERS, n);
        exit(0);
    }
    struct Node * players = list_create();  // список игроков
    
    int i;
    for (i = 0; i < n; i++) {
        Gamer * player = malloc(sizeof(Gamer));
        player->name = strdup("Gamer_");
        player->name + strlen("Gamer") = '0' + i;
        player->hand = list_create();
        list_push_back(players, player);
    }
    
    // read input deck
    Card * deck = malloc(sizeof(Card)*(strlen(line)/2));
    int j; // gamer index
    for(i = 0, j = 0; line[i]; i+=2, j++) {
        deck[j].rank = line[i];
        deck[j].suit = line[i+1];
        // printf("rank=%c %d, suit=%c %d\n", card.rank, card.rank, card.suit, card.suit);
        if (!valid_card(deck[j])) {
            fprintf(stderr, "Invalid card data: rank=%c suit=%c\n", card.rank, card.suit);
            exit(0);    // чтобы проверяющая система напечатала эту диагностику, а не свою истерику
        }
        list_push_back(hand[j%n], &deck[j]);    // раздаем карты по кругу по 1 карте
    }
    
    for(i = 0; i < n; i++) {
        printf("Gamer%d: ", i);
        hand_print(hand[i]);
        drop_pairs(hand[i]);
    }
    
    // передаем карты по кругу и сбрасываем пары
    int step;   // для отладки, если циклится, то заканчиваем после Х шагов передачу
    for(i = 0, step = 0; step < 10; i = (i+1)%n, step++){
        if (list_is_empty(hand[i]))     // уже сбросил все карты
            continue;
        // ищем следующего игрока, у которого есть рука
        int inext;
        for(inext = i+1; inext <= n; inext++)
            if (!list_is_empty(hand[inext%n]))
                break;
        printf("i=%d inext=%d\n", i, inext);
        if (inext == n+1){
            printf("The one gamer!\n");
            break;
        }
        inext = inext % n;
        // игрок i передает первую карту игроку inext
        struct Node * pcard = hand[i]->next;
        list_remove(pcard);
        list_insert_before(hand[inext], pcard);     // иначе они пиковую даму друг другу бесконечно пихают
        printf("Get card %c%c from Gamer%d to Gamer%d\n", 
            pcard->card()->rank, pcard->card()->suit, i, inext);
        printf("Gamer%d: ", i);
        hand_print(hand[i]);
        printf("Gamer%d: ", inext);
        hand_print(hand[inext]);
        drop_pairs(hand[inext]);
    }
    printf("Gamer%d is witch! ", i);
    hand_print(hand[i]);
    
    // Конец игры, освобождаем память
    for(i = 0; i < n; i++)
        list_clear(hand[i]);
    free(deck);
    free(line);
    return 0;
}
        