#pragma once

#include<ctime>
#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<thread>
#include<chrono>
#include<time.h>
#include<random>
#include<mutex>
#include<vector>
#include<list>

int random(int min, int max);

void gotoxy(short int x, short int y);

void hideCursor();

void setColor(WORD color = 7);

char cursorCharRead();

template<typename T>
void vector_erase(std::vector<T>& vec, T value) {
	auto it = find(vec.begin(), vec.end(), value);
	if (it != vec.end()) 
		vec.erase(it);
}


