
#include "map.h"
#include <string>
#include <fstream>
extern char map[25][60];
extern int currentLevel;
std::string Maps[10] = {"Maps/map1.txt","Maps/map2.txt","Maps/map3.txt","Maps/map4.txt","Maps/map5.txt","Maps/map6.txt","Maps/map7.txt","Maps/map8.txt","Maps/map9.txt","Maps/map10.txt",};
void openMap(int i)
{
	char Nmap[25][60];
	std::string line;
	std::ifstream mapz (Maps[i]);
	if (mapz.is_open())
	{
		int x = 0;
		while (getline(mapz,line))
		{
			for (unsigned int i = 0; i < line.length();++i)
			{
				if (line[i] == '#')
				{
					line[i] = (char)178;
				}
				if (line[i] == 'B')
				{
					line[i] = (char)177;
				}
			}
			for (int y = 0; y < 60;++y)
			{
				Nmap[x][y] = line[y];
			}
			++x;
		}	
	}
	mapz.close();
	mapData(Nmap);
	}

void mapData(char c[][60]) {

	for (int cols = 0; cols < 25; cols++)
	{
		for (int rows = 0; rows < 60; rows++)
		{
			if (c[cols][rows] == G_WALL)
			{
				c[cols][rows] = (char)178;
			}
			if (c[cols][rows] == G_BOX)
			{
				c[cols][rows] = (char)177;
			}
			map[cols][rows] = c[cols][rows];
		}
	}
}