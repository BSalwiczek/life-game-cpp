#include <iostream>
#include "Swiat.h"
#include <Windows.h>

using namespace std;


int main()
{

	Swiat* swiat = new Swiat();

	// Chowanie kursora w konsoli
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
	//-----------------------
	
	while (true)
	{
		swiat->rysujSwiat();
		swiat->czekajNaTure();
		swiat->wykonajTure();
	}

	delete swiat;

	return 0;
}