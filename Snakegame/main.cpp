#include <iostream>
#include "Map.h"
#include "Game.h"
#include "View.h"

using namespace std;

int main()
{

	View *v = new View();
	Game *g = new Game();
	Map *m = new Map();
	int gameCon;
	while(true)
	{
		system("cls");
		if(v->ShowMain()==2) 
		{
			v->SelectFood();
		}
		while(true){
			gameCon=0; 
			gameCon = g->Start(m,v);
			if(gameCon == 0 || gameCon == 2) 
				break;
		}
		if(gameCon == 0)
			break;
	}
	system("cls");

	delete m;
	delete g;
	delete v;
	return 0;
}