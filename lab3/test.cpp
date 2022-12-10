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
	int X0 = 40;
    int Y0 = Ymax - 30;
	int X1 = Xmax - 30;
    int Y1 = 30;
	int NX = X1 - X0;
	int NY = Y0 - Y1;

    line(X0, Y0, X0, Y1);
	line(X0, Y1, X1, Y1);
    char ox[9][4] = {"1PI", "2PI", "3PI", "4PI", "5PI", "6PI", "7PI", "8PI", "9PI"};
	char oy[7][1] = {'0', '1', '2', '3', '4', '5', '6'};
    // for(int i = 0; i < 10; i++)	//Рисуем метки и подписи на оси Х
	// {
	// 	line(X0 + (int)(NX/8) * i, Y1-3, X0 + (int)(NX/8) * i, Y1+3); //Метки
	// 	outtextxy(X0 + (int)(NX/8) * i, Y1-20, ox[i]); 	//Подписи
	// }

	for(int i = 0; i <= 6; i++)	//Рисуем метки и подписи на оси Y
	{
		line(X0 - 3, Y1 + (int)(NY/6) * i, X0 + 3, Y1 + (int)(NY/6) * i); //Метки
		//outtextxy(X0 - 20, (int)(NY/6) * i, oy[i]); 	//Подписи
	}


    getch();
}