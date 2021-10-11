#ifdef AAA
#include <stdio.h>

typedef struct
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
}Color;

// считать RGB-формат с консоли
Color getColor();
// перевод из RGB-формата в число
unsigned long long convertToHTML(Color);
// преобразование числа цвета в RGB-формат
Color convertToRGB(unsigned long long);
// печать цвета в RGB-формате (печать значений в десятичном виде через пробел)
// red green blue:
// 255 128 222
// Печатать только числа!!
void printRGB(Color);

// печать цвета в HTML-формате.
// Примеры: FFA902 0AA3FF
void printHTML(Color);

int main(){
    Color z, z2;
    unsigned long long html;
    
    z = getColor();
    printRGB(z);
    
    html = convertToHTML(z);
    printf("%llu\n", html);
    printHTML(z);
    
    z2 = convertToRGB(html);
    printRGB(z2);
    
    return 0;
}
#endif

typedef unsigned long long HTML;

// считать RGB-формат с консоли
Color getColor()
{
    Color res;
    unsigned int r, g, b;
    scanf("%u%u%u", &r, &g, &b);
    res.red = r;
    res.green = g;
    res.blue = b;
    return res;
}
// перевод из RGB-формата в число
unsigned long long convertToHTML(Color rgb)
{
    /* Старшие разряды соответствуют числу "red" RGB-формата, 
    следующие два - "green", 
    младшие - "blue"
    */
    unsigned long long res = 0;
    res = rgb.red;
    res = res * 256 + rgb.green;
    res = res * 256 + rgb.blue;
    return res;
    // return rgb.red * 256 * 256 + rgb.green * 256 + rgb.blue;
}   

// преобразование числа цвета в RGB-формат
Color convertToRGB(unsigned long long x)
{
    Color rgb;
    rgb.blue = x % 256;
    x = x / 256;
    rgb.green = x % 256;
    x = x / 256;
    rgb.red = x;
    return rgb;
}    
// печать цвета в RGB-формате (печать значений в десятичном виде через пробел)
// red green blue:
// 255 128 222
// Печатать только числа!!
void printRGB(Color rgb)
{
    printf("%u %u %u\n", rgb.red, rgb.green, rgb.blue);
}    

// печать цвета в HTML-формате.
// Примеры: FFA902 0AA3FF
void printHTML(Color rgb)
{
    printf("%X%X%X\n", rgb.red, rgb.green, rgb.blue);
}