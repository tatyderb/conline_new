#include <stdio.h>

#define N 101
#define NSCN "101"

#define BLACK -1
#define WHITE 0 
#define iscolored(x) ((x) > 0)  // проверяет, что клетка цветная

void read_field(char a[N][N], int n)
{
    for(int i = 0; i < n; i++)
        scanf("%" NSCN "s", a[i]);
}

// печатает поле или как * . и прочие символы,
void print_field(int n, char a[][N])
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%c", a[i][j]);
        }
        printf("\n");
    }
}
// или печатает числа в каждой клетке - "цвет" данной клетки
void print_int_field(int n, int a[][N+2])
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%2d ", a[i][j]);
        }
        printf("\n");
    }
}

// возвращает сколько символов * на поле
int black_counter(char a[N][N], int n)
{
    int black = 0;  // количество черных клеток
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (a[i][j] == '*')
                black ++;
            
    return black;
}

// отображает черно-белые клетки поля src на поле dst из *. в BLACK/WHITE нотацию,
// в поле dst добавляется со всех сторон ряд белых клеток
void map_to_number_field(int dst[N+2][N+2], char src[N][N], int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dst[i+1][j+1] = src[i][j] == '*' ? BLACK : WHITE;
}    

// раскрашивает черные клетки в цвет очередного прямоугольника и заполняет массив color
// color[i] - сколько клеток закрашено цветом if
void colorize_rectangles(int b[N+2][N+2], int n, int color[])
{
    int new_color = 0,  // цвет нового прямоугольника
        col = 0;        // в этот цвет будем перекрашивать клетку
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (b[i][j] == WHITE)
                continue;
            if (iscolored(b[i-1][j]))
                col = b[i-1][j];
            else if (iscolored(b[i][j-1]))
                col = b[i][j-1];
            else
                col = ++new_color;
                
                
            b[i][j] = col;
            color[col] ++;
        }
    }
}

typedef struct {
    int i, j;
} Point;
// если клетка b[i][j] черная, то кладем ее в конец очереди,
// возвращаем указатель на новый конец очереди
Point * try_to_enqueue(int b[N+2][N+2], int i, int j, Point * end)
{
    Point t;
    if (b[i][j] == BLACK) {
        t.i = i;
        t.j = j;
        *end++ = t;
    }
    return end;
}    
// раскрашивает фигуру в цвет color начиная с поля b[i][j]
void color_figure(int b[N+2][N+2], int i, int j, int color)
{
    static Point queue[N*N*4];      // очередь, делать ее эффективной мне лениво, поэтому оценка сверху по длине
    static Point * head = queue;    // указатель на первый элемента с данными 
    static Point * end = queue;     // указатель на первый пустой элемент в конце очереди
    
    // если клетку уже обработали, еще раз ее обрабатывать не нужно
    if (b[i][j] != BLACK)
        return;
    
    // положили первую точку фигуры в очередь
    Point todo;
    todo.i = i;
    todo.j = j;
    *head = todo;
    end++;
    
    while (head < end) {
        // берем точку из очереди
        i = head->i;
        j = head->j;
        head ++;
        b[i][j] = color;
        
        // кладем в очередь её черных соседей
        end = try_to_enqueue(b, i-1, j, end);
        end = try_to_enqueue(b, i+1, j, end);
        end = try_to_enqueue(b, i, j-1, end);
        end = try_to_enqueue(b, i, j+1, end);
    }
} 
   
// раскрашивает черные клетки в цвет очередной фигуры и заполняет массив color
// color[i] - сколько клеток закрашено цветом i
int colorize_figures(int b[N+2][N+2], int n)
{
    
    int new_color = 0;  // цвет нового прямоугольника
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (b[i][j] == WHITE || iscolored(b[i][j]))
                continue;
            color_figure(b, i, j, ++new_color);
        }
    }
    return new_color;
}

// возвращает максимальное число в массиве
int max_number(int * a, int n)
{
    int max = a[0];
    for(int i = 1; i < n; i++)
        if (max < a[i])
            max = a[i];
    return max;
}

void print_arr_nonzero(int color[])
{
    for(int i = 1; color[i] > 0; i++)
        printf("%d: %d\n", i, color[i]);
}

int main()
{
    char a[N][N];   // поле символов
    int n;          // размер поля символов
    
    /* каждый новый прямоугольник имеет новый цвет от 1 до ... */
    int b[N+2][N+2] = {};   // поле закрашенных прямоугольников
    
    scanf("%d", &n);
    read_field(a, n);
    print_field(n, a);
    
    map_to_number_field(b, a, n);
    print_int_field(n+2, b);
    
    // предыдущая задача с прямоугольниками
    // int color[N*N] = {};    // color[i] - площадь прямоугольника цвета i
    // colorize_rectangles(b, n, color);
    // printf("%d\n", max_number(color, N*N));
    
    printf("%d\n", colorize_figures(b, n));
    print_int_field(n+2, b);
    
    
    return 0;
}
