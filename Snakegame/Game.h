#pragma once
#include <Windows.h>
#include "View.h"
#include "Map.h"

struct Point
{
	int x;
	int y;
};

class Game
{
	int watch; 
	int flowWatch; 
	int h_x,h_y; 
	Point sp[50]; 
	int direction; 
	int bodyLen; 
	int eat; 
	int gameCon; 
	int MoveSpeed; 
	int foodCount; 
	int stage; 
public:
	Game();
	int Start(Map *m, View *v); 
	void Stop(View *v,bool win = false); 
	void Reset(); 
	void SpeedUp(); 
	void Born(Map *m); 
	void SetFood(Map *m,View *v); 
	int HoldTime(); 
	int PlayTime(); 
	int GetX(); 
	int GetY(); 
	void Moving(Map *m, View *v, int _h_x, int _h_y); 
	void Up(Map *m, View *v); 
	void Down(Map *m, View *v); 
	void Left(Map *m, View *v); 
	void Right(Map *m, View *v);
	void Move(Map *m, View *v); 
};