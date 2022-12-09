#include "math.h"
#include "graphics.h"
#include "iostream"
#include <conio.h>

int main()
{
    int driver = DETECT, mode;
    initgraph(&driver, &mode, "c://turboc3//bgi");
    int Xmax = getmaxx();
    int Ymax = getmaxy();
    int X1 = 40;
    int X2 = Xmax - 40;
    int Y1 = 50;
    int Y2 = Ymax - 70;
    int N = X2 - X1 - 47 - 26;

    int i;
    for (i = 1; i < 19; ++i)
        line(X1 - 5, Y2 - i * 20, X1 + 5, Y2 - i * 20);
    for (i = 1; i < 17; ++i)
        line(X1 + 35 * i, Y2 + 5, X1 + 35 * i, Y2 - 5);
    
    char xi[14][2];
    for (i = 4; i < 61; i += 4)
    {
        sprintf(xi[i / 4 - 1], "%dp/2", i/4);
        outtextxy(X1 + 15.45 * i / 2 + i - 3, Y2 + 7, xi[i / 4 - 1]);
    }

    char yi[14][2];
    for (i = 2; i < 19; i += 2)
    {
        sprintf(yi[i / 2 - 1], "%d", i / 2);
        outtextxy(X1 - 20, Y2 - 20 * i - i / 4, yi[i / 2 - 1]);
    }
    getch();
}