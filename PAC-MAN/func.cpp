#include "func.h"


int random(int min, int max)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(min, max); // distribution in range [min, max]

	return dist6(rng);
}

void gotoxy(short int x, short int y) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x,y };
	SetConsoleCursorPosition(handle, pos);
}

void hideCursor()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(h, &info);
}

void setColor(WORD color)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, color);
}

char cursorCharRead()
{
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &csbiInfo);
	COORD pos = csbiInfo.dwCursorPosition; //set pos to current cursor location
	TCHAR strFromConsole[1];    //need space to only one char
	DWORD dwChars;
	ReadConsoleOutputCharacter(
		hConsole,
		strFromConsole, // Buffer where store symbols
		1, // Read 1 char to strFormConsole
		pos, // Read from current cursor position
		&dwChars); // How many symbols stored
	char c = strFromConsole[0];
	return c;
}
