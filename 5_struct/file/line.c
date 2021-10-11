#include <stdio.h>
#include <math.h>
#include <assert.h>

typedef struct {
    int x;
    int y;
} Point;  
typedef struct{
    Point a;
    Point b;
} Line;    
  
// Работаем с точкой
void printPoint(Point p);
void scanPoint(Point * p);          // scanPoint(&p);

float distance(Point p1, Point p2);
int is_equal(Point p1, Point p2);

Point movePoint1(Point p, int dx);       // x = inc(x);
void movePoint2(Point * p, int dx);      // inc(&x);

// Работаем с отрезком
void printLine(Line p);
void scanLine(Line * p);          // scanLine(&p);

float length(Line p1);
int is_equalLine(Line p1, Line p2);

Line moveLine1(Line p, int dx);       // x = inc(x);
void moveLine2(Line * p, int dx);      // inc(&x);


void testPoint()
{
    Point p1 = {4, 3};
    Point p2 = {-4, -3};
    printPoint(p1);     // (4,3)
    
    float d = distance(p1, p2);
    assert(d == 10);

    Point p_new = movePoint1(p1, 2);     // 6, 3
    printPoint(p_new);
    Point exp_point = {6, 3};
    assert(is_equal(exp_point, p_new));
    
    exp_point.x += 2;
    movePoint2(&p_new, 2);
    printPoint(p_new);              // 8, 3
    assert(is_equal(exp_point, p_new));
    
    Point t;
    scanPoint(&t);
    printPoint(t);
    
    printf("\n");
}    
int main()
{
    Line s = {{2, 3}, {5, 7}};
    printLine(s);
    assert(length(s) == 5);
    printf("length=%.2f\n", length(s));
    
    Line s_new = moveLine1(s, 3);
    printLine(s_new);
    Line exp_line = {{5, 3}, {8, 7}};
    assert(is_equalLine(s_new, exp_line));

    exp_line.a.x += 3;
    exp_line.b.x += 3;
    moveLine2(&s_new, 3);
    printLine(s_new);
    assert(is_equalLine(s_new, exp_line));
    
    Line s3 = readLine();
    printLine(s3);
    
    Line s4;
    scanLine(&s4);
    printLine(s4);
    
    return 0;
}
Line readLine()
{
    Line res;
    res.a = readPoint();
    res.b = readPoint();
    return res;
}
void scanLine(Line * p)
{
    // scanLine(&p);
    scanPoint(&p->a);
    scanPoint(&p->b);
}
void moveLine2(Line * p, int dx)
{
    movePoint2( &p->a, dx);
    movePoint2( &p->b, dx);
}    
Line moveLine1(Line s, int dx)
{
    Line res;
    res.a = movePoint1(s.a, dx);
    res.b = movePoint1(s.b, dx);
    return res;
}

float length(Line p1)
{
    return distance(p1.a, p1.b);
}    
int is_equalLine(Line p1, Line p2)
{
    return is_equal(p1.a, p2.a) && is_equal(p1.b, p2.b);
}
void printLine(Line p)
{
    // printf("(%d,%d) (%d,%d)", p.a.x, p.a.y, p.b.x, p.b.y); 
    printPoint(p.a);
    printPoint(p.b);
    printf("\n");
}
void scanPoint(Point * p)
{
    int x, y;
    scanf("%d%d", &x, &y);
    p->x = x;
    p->y = y;
}

void movePoint2(Point * p, int dx)
{
    p->x += dx;
}
Point movePoint1(Point p, int dx)
{
    Point res = p;
    res.x += dx;
    return res;
}

int is_equal(Point p1, Point p2)
{
    return p1.x == p2.x && p1.y == p2.y;
}    

float distance(Point p1, Point p2)
{
    int dx = p1.x - p2.x;
    int dy = p1.y - p2.y;
    return sqrt(dx*dx + dy*dy);
}
 
void printPoint(Point p)
{
    printf("(%d,%d) ", p.x, p.y);
}