#pragma once
#include"GameFunc.h"
#include"Entity.h"
#include"Pac_man.h"

class Ghost : public Entity
{
private:
	static bool is_prey;
protected:
	void moveCharacter(int x, int y) override;
	char symbol_behind = ' ';
public:
	Ghost(int x, int y);
	static void prey_mod(bool state);
	Direction getNextDir();
	void changeDirAndMove(Direction dir) override;
	void die() override;
	void toBeginning();
};


