#include"func.h"
#include"GameFunc.h"
#include"Pac_man.h"
#include"Ghost.h"

using namespace std;

int main() {
	
    hideCursor();
	system("mode con cols=25 lines=15");


	bool programm_run = true;
	bool game_run = true;
	int key;
	int i;
	int lives = 3;
	drawMap();


	//creating an pac_man
	Pac_man* pacman = Pac_man::getInstance();
	clock_t pacman_time = clock();

	//creating ghosts
	const int g_num = 3;
	Ghost g[g_num]{Ghost(11,4), Ghost(11,4), Ghost(11,4)};
	clock_t g_time[g_num]{ 4000, 8000, 12000 };


	//individual thread for keyboard input
	thread th(getKey, std::ref(key));
	th.detach();


	while (programm_run) {

		while (game_run) {

			//ghost movement
			for (i = 0; i < g_num; i++) {
				if (clock() - g_time[i] >= 230) {
					g[i].changeDirAndMove(g[i].getNextDir());
					g_time[i] = clock();
				}
			}

			//murder
			for (i = 0; i < g_num; i++) {
				if (pacman->GetX() == g[i].GetX() && pacman->GetY() == g[i].GetY()) {
					if (pacman->isHunter()) {
						g[i].die();
						g_time[i] = clock() + 4000;
					}
					else {
						pacman->die(); lives--;
						for (i = 0; i < g_num; i++) g[i].toBeginning();
						for (i = 0; i < g_num; i++) g_time[i] = clock() + (i + 1) * 4000;
						break;
					}
				}
			}

			//pacman movement
			if ((!pacman->isHunter() && clock() - pacman_time >= 250) || (pacman->isHunter() && clock() - pacman_time >= 210)) {
				switch (key) {
				case 72://up
				case 87://W	
				case 119://w
					pacman->changeDirAndMove(Direction::UP);
					break;
				case 80://down
				case 83://S
				case 115://s
					pacman->changeDirAndMove(Direction::DOWN);
					break;
				case 75://left
				case 65://A
				case 97://a
					pacman->changeDirAndMove(Direction::LEFT);
					break;
				case 77://right
				case 68://D
				case 100://d
					pacman->changeDirAndMove(Direction::RIGHT);
					break;
				case 27://escape
					game_run = false;
					break;
				case 32://space 
					break;
				}
				pacman_time = clock();
			}

			//murder
			for (i = 0; i < g_num; i++) {
				if (pacman->GetX() == g[i].GetX() && pacman->GetY() == g[i].GetY()) {
					if (pacman->isHunter()) {
						g[i].die();
						g_time[i] = clock() + 4000;
					}
					else {
						pacman->die(); lives--;
						for (i = 0; i < g_num; i++) g[i].toBeginning();
						for (i = 0; i < g_num; i++) g_time[i] = clock() + (i + 1) * 4000;
						break;
					}
				}
			}

			if (!isThereAnyFood() || lives < 1) game_run = false;


		}

		system("cls");
		gotoxy(0, 10); cout << "SPACE, ENTER -> RESTART";
		gotoxy(0, 11); cout << "ESCAPE -> EXIT";


		switch (key) {
		case 27://escape
			programm_run = false;
			break;
		case 32://space
		case 13://enter
			drawMap();
			game_run = true;
			pacman->die();
			for (i = 0; i < g_num; i++) g[i].toBeginning();
			for (i = 0; i < g_num; i++) g_time[i] = clock() + (i + 1) * 4000;
			lives = 3;
			break;
		}


	}
	system("cls");
	return 0;
}