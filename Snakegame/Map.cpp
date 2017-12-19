#include "Map.h"

int Map::GetMap(int stage = 0)
{
	string mapName;
	switch(stage)
	{
	case 0: mapName="Stage1.txt"; break;
	case 1: mapName="Stage2.txt"; break;
	case 2: mapName="Stage3.txt"; break;
	case 3: mapName="Stage4.txt"; break;
	case 4: mapName="Stage5.txt"; break;
	default: mapName="Stage1.txt"; break;
	}

	ifstream mapin(mapName);
	if(!mapin)
	{
		DefaultMap(); 
		ofstream mapout(mapName);

		for(int i=0;i<MAP_X;i++)
		{
			for(int j=0;j<MAP_X;j++)
			{
				mapout<<map[i][j]<<" ";
			}
			mapout<<endl;
		}

		mapout.close();
		return 0;;
	}
	for(int i=0;i<MAP_X;i++)
	{
		for(int j=0;j<MAP_X;j++){
			mapin>>map[i][j];
		}
	}

	mapin.close();
	return 0;
}

void Map::DefaultMap() 
{
	int temp=0;

	for(int i=0;i<MAP_X;i++)
	{
		for(int j=0;j<MAP_X;j++)
		{
			map[i][j] = 0;
		}
	}

	for(int i=0;i<MAP_X;i++)
	{
		map[0][i] = 1;
		map[MAP_X-1][i] = 1;
		map[i][0] = 1;
		map[i][MAP_X-1] = 1;
	}
}

int Map::GetMapValue(int x, int y)
{
	return map[y][x];
}

void Map::SetMapValue(int x, int y, int value)
{
	map[y][x] = value;
}