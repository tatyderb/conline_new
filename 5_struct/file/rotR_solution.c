#include <stdio.h>
#include <math.h>

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point a;    // начало отрезка
    Point b;    // конец отрезка
    float len;  // длина отрезка
} Line;

float distance(Point a, Point b);   // расстояние между точками
void scanLine(Line * t);
void printLine(Line t);
void rotRLine(Line * t);

int main() {
    Line t;
    
    scanLine(&t);
    rotRLine(&t);
    printLine(t);
    
    return 0;
}

float distance(Point a, Point b)
{   
    // расстояние между точками
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return sqrt(dx*dx + dy*dy);
}
/*
void scanPoint(Point * p)
{
    scanf("%d%d", &p->x, &p->y);
}    
void scanLine(Line * t)
{
    scanPoint(&t->a);
    scanPoint(&t->b);
    t->len = distance(t->a, t->b);
}
*/
void scanLine(Line * t)
{
    scanf("%d%d%d%d", &t->a.x, &t->a.y, &t->b.x, &t->b.y);
    t->len = distance(t->a, t->b);
}
void printLine(Line t)
{
    printf("%d %d %d %d %.3f\n", t.a.x, t.a.y, t.b.x, t.b.y, t.len);   
}    
void rotRPoint(Point * p)
{
    int xnew = p->y;
    int ynew = - p->x;
    p->x = xnew;
    p->y = ynew;
}    
void rotRLine(Line * t)
{
    rotRPoint(&t->a);
    rotRPoint(&t->b);
}