#include "Pac_man.h"

bool Pac_man::is_hunter = false;
Pac_man* Pac_man::pinstance_ = nullptr;
std::mutex Pac_man::mutex_;

bool modOff = false;

Pac_man* Pac_man::getInstance()
{
	std::lock_guard<std::mutex> lock(mutex_);
	if (pinstance_ == nullptr)
		pinstance_ = new Pac_man;

	return pinstance_;
}

void Pac_man::hunter_mod(bool state)
{
	is_hunter = state;
}

Pac_man::~Pac_man() {
	delete pinstance_;
}

void Pac_man::changeDirAndMove(Direction dir) {

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

	//if in new direction there is an barrier, pac-man keep on moving in the past direction
	if (!check_barr(l_x, l_y)) {
		moveCharacter(l_x, l_y);
		this->past_dir = dir;
	}
	else if (this->past_dir != dir)
		changeDirAndMove(past_dir);
}

void Pac_man::moveCharacter(int x, int y) {

	gotoxy(this->pos_x, this->pos_y);
	if (this->pos_x == 0 || this->pos_x == 24 && this->pos_y == 6) // draw the teleport back
		setColor(BACKGROUND_INTENSITY | BACKGROUND_BLUE);
	std::cout << ' ';
	
	this->pos_x = x;
	this->pos_y = y;

	setColor(FOREGROUND_RED | FOREGROUND_GREEN);
	gotoxy(this->pos_x, this->pos_y);
	if (cursorCharRead() == '-'){
		eatFood();
	}
	else if (cursorCharRead() == 'O') {

		std::thread hunterMod([]() {			
			Pac_man::hunter_mod(1);
			Ghost::prey_mod(1);
			if (modOff) {
				modOff = false;
				std::this_thread::sleep_for(std::chrono::milliseconds(6000));
				if (!modOff) {
					Pac_man::hunter_mod(0);
					Ghost::prey_mod(0);
				}
			}
			else {
				modOff = true;
				std::this_thread::sleep_for(std::chrono::milliseconds(6000));
				if (modOff) {
					Pac_man::hunter_mod(0);
					Ghost::prey_mod(0);
				}
			}
			});

		hunterMod.detach();

	}
	std::cout << '@';
}

void Pac_man::die()
{
	setColor(BACKGROUND_RED | BACKGROUND_GREEN);
	gotoxy(pos_x, pos_y); std::cout << '!';
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	setColor();
	gotoxy(pos_x, pos_y); std::cout << ' ';
	this->pos_x = 11;
	this->pos_y = 11;
	setColor(FOREGROUND_RED | FOREGROUND_GREEN);
	gotoxy(pos_x, pos_y); std::cout << '@';
	setColor();
}
