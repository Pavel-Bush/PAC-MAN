#include"GameFunc.h"

const int BARR_ROWS = 15, BARR_COLUMNS = 25;
bool barriers[BARR_ROWS][BARR_COLUMNS]{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1},
	{1,0,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,1,1,0,1,0,0,0,1},
	{1,0,0,0,0,0,0,1,0,1,1,0,1,1,0,1,0,1,1,0,0,0,1,0,1},
	{1,0,1,0,1,1,1,1,0,1,1,1,1,1,0,1,0,1,1,0,1,0,1,1,1},
	{0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0,0},
	{1,0,1,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,1,0,1,1,1,0,1},
	{1,0,0,0,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,0,1,0,0,0,1},
	{1,1,0,1,0,1,0,0,0,1,0,1,0,0,0,1,1,0,1,0,0,0,1,1,1},
	{1,1,0,1,0,1,1,1,1,1,0,1,1,1,0,1,1,0,1,1,1,1,1,1,1},
	{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,0,1,1,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,1,0,1},
	{1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
int food = 169;

std::vector<std::pair<int, int>> snickers_coord {
std::make_pair(6,4),
std::make_pair(6,13),
std::make_pair(23,4),
std::make_pair(23,11) };


void drawMap()
{
	//draw food
	setColor(FOREGROUND_INTENSITY);
	for (int i = 0; i < 15; i++)
		std::cout << "-------------------------";

	//draw barriers
	setColor(BACKGROUND_RED);
	for (int iY = 0; iY < BARR_ROWS; iY++) {
		for (int iX = 0; iX < BARR_COLUMNS; iX++) {
			if (barriers[iY][iX]) {
				gotoxy(iX, iY);
				std::cout << ' ';
			}
		}
	}

	//draw snickers
	setColor(FOREGROUND_INTENSITY);
	for (auto it : snickers_coord) {
		gotoxy(it.first, it.second);
		std::cout << 'O';
	}

	//draw teleports
	setColor(BACKGROUND_INTENSITY | BACKGROUND_BLUE);
	gotoxy(0, 6); std::cout << ' ';
	gotoxy(24, 6); std::cout << ' ';

	//draw pacman
	setColor(FOREGROUND_RED | FOREGROUND_GREEN);
	gotoxy(11, 11); std::cout << '@';

	//draw ghosts
	setColor(FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	gotoxy(11, 4); std::cout << '$';


	setColor();
}


bool check_barr(int x, int y)
{
	return barriers[y][x];
}

bool check_barr_range(int x1, int y1, int x2, int y2)
{
	for (x1; x2 < x2; x1++) 
		for (y1; y1 < y2; y1++) 
			if (check_barr(x1, y1)) 
				return true;	
	return false;
}

void getKey(int& key)
{
	while (1) {
		key = _getch();
	}
}


void eatFood()
{
	food--;
}

bool isThereAnyFood()
{
	return (food > 0);
}
