#pragma once
#include"GameFunc.h"

class Entity
{
protected:
	int pos_x = 0, pos_y = 0;
	Direction past_dir = DOWN;
	virtual void moveCharacter(int x, int y) = 0;
public:
	virtual void changeDirAndMove(Direction dir) = 0;
	virtual void die() = 0;
	
	int GetX() { return pos_x; }
	int GetY() { return pos_y; }

};

