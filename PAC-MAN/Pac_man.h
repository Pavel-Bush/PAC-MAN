#pragma once

#include"GameFunc.h"
#include"Entity.h"
#include"Ghost.h"

class Pac_man: public Entity
{
private:
	static bool is_hunter;
	static Pac_man* pinstance_;
	static std::mutex mutex_;
protected:

	Pac_man() { pos_x = 11; pos_y = 11; };
	void moveCharacter(int x, int y) override;
public:

	Pac_man(Pac_man const&) = delete;
	void operator=(Pac_man const&) = delete;
	static Pac_man* getInstance();

	void changeDirAndMove(Direction dir) override;
	void die() override;
	static void hunter_mod(bool state);
	bool isHunter() { return is_hunter; }
	~Pac_man();
	
};

