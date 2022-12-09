#include "math.h"
#include "graphics.h"
#include "iostream"
#include <conio.h>

int main()
{
    system("cls");
    int DRIVER, MODE;
	detectgraph(&DRIVER,&MODE);
	initgraph(&DRIVER,&MODE,"c://turboc3//bgi");

	int Xmax = getmaxx(); 
	int Ymax = getmaxy(); 
	int X0 = 40;
    int Y0 = Ymax - 30;
	int X1 = Xmax - 30;
    int Y1 = 30;
	int N = X1 - X0;
	
    char Ox[9][4] = {"1PI", "2PI", "3PI", "4PI", "5PI", "6PI", "7PI", "8PI", "9PI"};
	setlinestyle(0,1,1); 
	outtextxy(200, 400, "f(x)=cos^3(x/2) - sqrt(x) on PI to 9PI");
	
	setlinestyle(0, 1, 2);            // Координатные оси
	line(X0, Y0, X0, Y1);
	line(X0, Y1, X1, Y1);

	outtextxy(X0, Y0, "f(x)");
	outtextxy(X1 + 3, Y1, "x");
	outtextxy(X0 - 30, Y1 - 20, "0");
	outtextxy(X0 - 10, Y0 - 20, "1");
		
	for(int i = 0; i < 10; i++)	//Рисуем метки и подписи на оси Х
	{
		line(X0 + (int)(N/8) * i, Y1-3, X0 + (int)(N/8) * i, Y1+3); //Метки
		outtextxy(X0 + (int)(N/8) * i, Y1-20, Ox[i]); 	//Подписи
	};

	const double PI = 3.1415926535;
    double result[N] = {0};
	double x = PI;
	double xmax = 9 * PI;
    double dx = (xmax - x) / N;
    double max = -10.;
	for (int i = 0; i < N; i++)
	{
		result[i] = (double)(pow(cos(x/2), 3) - sqrt(x));  //сама функция
		if(max < result[i]) max = result[i];
        x += dx;
    }
	
    int normalizedDots[N] = {0};
	for (int i = 0; i < N; i++)
    {
		normalizedDots[i] = (int)(result[i] / (result[0] + result[N-1]) * (double)(Y0 - Y1));
	}
	// Рисуем график функции
	for(int i = 0; i < N; ++i)
	{
		putpixel(X0+i, normalizedDots[i], 14);  // 12 - это цвEт линии графика
		//delay(10);
	}
		
	outtextxy(200, 50, "Maximum of F(x) is ________________");
	getch();
	closegraph();
	getch();  
}