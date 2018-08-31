#ifndef DESIGN_H
#define DESIGN_H
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
class design{
	public:
		void gotoxy(int x, int y);
		static void SetColor(int ForgC);
		void cursor(bool showFlag);
		void menu();
		void registro();
		void cargando();
		void s_ticket();
	protected:
		
};

 	void design::gotoxy(int x,int y){  
      	HANDLE hcon;  
      	hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      	COORD dwPos;  
      	dwPos.X = x;  
      	dwPos.Y= y;  
      	SetConsoleCursorPosition(hcon,dwPos);  
 	} 
	void design::SetColor(int ForgC){
 		WORD wColor;
  		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  		CONSOLE_SCREEN_BUFFER_INFO csbi;

    	//We use csbi for the wAttributes word.
 		if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
 		{	
        //Mask out all but the background attribute, and add in the forgournd color
      		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
      		SetConsoleTextAttribute(hStdOut, wColor);
 			}
				}		
void design::cursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO     cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}
void design::menu(){
	gotoxy(20,2);
	SetColor(15);
	printf("** AUTENTICACION UNICA **");
}
void design::registro(){
	SetColor(15);
	gotoxy(20,2);printf("** CREAR UNA NUEVA CUENTA **");	
}
void design::cargando(){
	cursor(false);
	SetColor(15);
	gotoxy(5,9);printf("Ingresando al sistema.");
	Sleep(1000);
	gotoxy(27,9);printf(".");
	Sleep(1000);
	gotoxy(28,9);printf(".");
	Sleep(1000);
	gotoxy(29,9);printf(".");
	Sleep(1000);		
}
#endif
