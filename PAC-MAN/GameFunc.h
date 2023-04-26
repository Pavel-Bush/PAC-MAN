#pragma once

#include"func.h"

enum Direction {
	LEFT, RIGHT, UP, DOWN
};

void drawMap();

bool check_barr(int x, int y);

bool check_barr_range(int x1, int y1, int x2, int y2);

void getKey(int& key);

void eatFood();

bool isThereAnyFood();