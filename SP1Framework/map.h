#ifndef _MAP_H
#define _MAP_H


enum GAMEOBJ
{
	G_WALL = '#',
	G_BOX = 'B',
	G_PORT = '@'
};

void mapData(char c[][60]);
void openMap(int i);

#endif // _MAP_H