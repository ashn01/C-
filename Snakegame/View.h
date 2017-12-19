#pragma once

#include <Windows.h>
#include <iostream>
#include <conio.h>
#include "Map.h"

using namespace std;
class View
{
	int ans; 
	char* foodType; 
	int foodSelect; 
public:
	View();
	int ShowMain(); 
	void ShowMap(Map* m);
	void SelectFood(); 
	void ShowPlayTime(int time); 
	void ShowLocation(int h_x, int h_y);
	void Eat_N_RemainingFood(int eat, int remainingfood);
	void Head(int x, int y); 
	void Clear(int x, int y); 
	void Body(int x, int y);
	void GameSet(); 
	void NoBlink(); 
	void StageClear(int stage); 
	void Win(); 
	void SetColor(int color,int bgcolor); 
};