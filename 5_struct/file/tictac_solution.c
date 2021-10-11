#ifdef AAA
#include <stdio.h>
#include <stdlib.h>
#define WEEK 10080
typedef struct{
	int h;
	int min;
}TicTac;

TicTac after(TicTac a, int min);
void forward(TicTac * me, TicTac a);
void backward(TicTac * me, TicTac a);
void printTic(TicTac a);
int isEqualTime(TicTac a, TicTac b);

int main(){
    TicTac a,b,c;
    int mk;
    
    scanf("%d:%d", &(a.h), &(a.min));
    scanf("%d", &mk);
    scanf("%d:%d", &(b.h), &(b.min));
    
    printf("equal: %d\n",isEqualTime(a,b));
    c = after(a, mk);
    printf("after: ");
    printTic(c);
    
    c = a;
    printf("forward: ");
    forward(&a, b);
    printTic(a);
    
    printf("backward: ");
    backward(&c, b);
    printTic(c);
    
    return 0;
}

#endif

int time2min(TicTac a)
{
    return a.h * 60 + a.min;
}
TicTac min2time(int m)
{
    TicTac res;
    res.min = m % 60;
    res.h = m / 60 % 12;
    return res;
}

// получает показание часов a и возвращает показание этих часов
// через min минут, .
TicTac after(TicTac a, int min)
{
    return min2time(min + time2min(a));
}

// "переводит" вперед стрелки этих часов (me)
// на a.h часов и a.min минут
void forward(TicTac * me, TicTac a)
{
    * me = min2time(time2min(*me) + time2min(a));
}

// "переводит" назад стрелки этих часов (me)
// на a.h часов и a.min минут
void backward(TicTac * me, TicTac a)
{
    a = min2time(time2min(a));                          // a < 12:00
    *me = min2time(time2min(*me) + 12*60 - time2min(a));
}    

// проверяет совпадают ли показания часов a и b
// если совпадают, возвращает 1, если нет - 0
int isEqualTime(TicTac a, TicTac b)
{
    return time2min(a) == time2min(b);
}

// печатает показания этих часов в формате hh:mm\n
void printTic(TicTac a)
{
    printf("%02d:%02d\n", a.h, a.min);
}