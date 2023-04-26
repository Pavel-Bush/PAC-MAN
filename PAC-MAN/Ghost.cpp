#include "Ghost.h"

bool Ghost::is_prey = false;

Direction Ghost::getNextDir()
{
	std::vector<Direction> allowed_dir = { UP, DOWN, RIGHT, LEFT };
	//delete the direction where is a barrier
	if (check_barr(pos_x, pos_y + 1)) vector_erase(allowed_dir, Direction::DOWN);;
	if (check_barr(pos_x, pos_y - 1)) vector_erase(allowed_dir, Direction::UP);;
	if (check_barr(pos_x - 1, pos_y) && pos_x != 0) vector_erase(allowed_dir, Direction::LEFT);;
	if (check_barr(pos_x + 1, pos_y) && pos_x != 24) vector_erase(allowed_dir, Direction::RIGHT);;
	
	if (allowed_dir.size() > 1) {
		//delete the direction opposite to the previouse one if there is no gridlock
		switch (this->past_dir) {
		case UP: 
			vector_erase(allowed_dir, Direction::DOWN); break;
		case DOWN:
			vector_erase(allowed_dir, Direction::UP); break;
		case RIGHT:
			vector_erase(allowed_dir, Direction::LEFT); break;
		case LEFT:
			vector_erase(allowed_dir, Direction::RIGHT); break;
		}

		//defining where the pac-man is and increasing the chance of movement in his direction
		Pac_man* pac = Pac_man::getInstance();
		int pac_x = pac->GetX();
		int pac_y = pac->GetY();
		
		if (pac_x == pos_x) {
			if (pac_y < pos_y &&
				std::find(allowed_dir.begin(), allowed_dir.end(), UP) != allowed_dir.end() &&
				!check_barr_range(pac_x, pos_x, pac_y, pos_y))
				return UP;
			else if (pac_y > pos_y &&
				std::find(allowed_dir.begin(), allowed_dir.end(), DOWN) != allowed_dir.end() &&
				!check_barr_range(pos_x, pac_x, pos_y, pac_y))
				return DOWN;
		}

		if (pac_y == pos_y) {
			if (pac_x < pos_x &&
				std::find(allowed_dir.begin(), allowed_dir.end(), LEFT) != allowed_dir.end() &&
				!check_barr_range(pac_x, pos_x, pac_y, pos_y))
				return LEFT;
			else if (pac_x > pos_x &&
				std::find(allowed_dir.begin(), allowed_dir.end(), RIGHT) != allowed_dir.end() &&
				!check_barr_range(pos_x, pac_x, pos_y, pac_y))
				return RIGHT;
		}

		if (pac_x - pos_x > 0 && std::find(allowed_dir.begin(), allowed_dir.end(), RIGHT) != allowed_dir.end()) 
			allowed_dir.push_back(RIGHT);
		else if(pac_x - pos_x < 0 && std::find(allowed_dir.begin(), allowed_dir.end(), LEFT) != allowed_dir.end())
			allowed_dir.push_back(LEFT);
		if (pac_y - pos_y > 0 && std::find(allowed_dir.begin(), allowed_dir.end(), DOWN) != allowed_dir.end())
			allowed_dir.push_back(DOWN);
		else if (pac_y - pos_y < 0 && std::find(allowed_dir.begin(), allowed_dir.end(), UP) != allowed_dir.end())
			allowed_dir.push_back(UP);
	}

	return allowed_dir[random(0, 1199) / (1200 / allowed_dir.size())];
}

void Ghost::moveCharacter(int x, int y)
{
	setColor(FOREGROUND_INTENSITY);
	gotoxy(this->pos_x, this->pos_y);
	if (this->pos_x == 0 || this->pos_x == 24 && this->pos_y == 6) // draw the teleport back
		setColor(BACKGROUND_INTENSITY | BACKGROUND_BLUE);
	std::cout << symbol_behind;

	this->pos_x = x;
	this->pos_y = y;

	setColor((is_prey)?(FOREGROUND_INTENSITY):(FOREGROUND_INTENSITY | FOREGROUND_GREEN));
	gotoxy(this->pos_x, this->pos_y);
	symbol_behind = cursorCharRead();
	if (symbol_behind == '$' || (symbol_behind == '@' && is_prey)) {
		symbol_behind = '\0';
	}
	else std::cout << '$';
}

Ghost::Ghost(int x, int y)
{
	pos_x = x;
	pos_y = y;
}

void Ghost::prey_mod(bool state)
{
	is_prey = state;
}

void Ghost::changeDirAndMove(Direction dir)
{

	int l_x = this->pos_x, l_y = this->pos_y;
	switch (dir) {
	case Direction::UP:
		l_y--;
		break;
	case Direction::DOWN:
		l_y++;
		break;
	case Direction::LEFT:
		l_x--;
		if (l_x == -1) l_x = 24; //teleport
		break;
	case Direction::RIGHT:
		l_x++;
		if (l_x == 25) l_x = 0; //teleport
		break;
	}

	moveCharacter(l_x, l_y);
	this->past_dir = dir;

}

void Ghost::die()
{
	pos_x = 11;
	pos_y = 4;
	past_dir = UP;
	if (symbol_behind == '-')eatFood();
	symbol_behind = ' ';
}

void Ghost::toBeginning()
{
	setColor();
	gotoxy(pos_x, pos_y);
	if(symbol_behind != '@')
		std::cout << symbol_behind;
	symbol_behind = ' ';
	pos_x = 11;
	pos_y = 4;
	setColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	gotoxy(pos_x, pos_y);
	std::cout << '$';
}
