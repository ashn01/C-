#pragma once

#include <fstream>
#include <Windows.h>
#include <iostream>
#include <random>
#include <time.h> 
#include <string>
#define MAP_X 23

using namespace std;
class Map
{
	int map[MAP_X][MAP_X]; 
public :
	int GetMap(int stage); 
	void DefaultMap(); 
	int GetMapValue(int x, int y); 
	void SetMapValue(int x, int y, int value); 
};