#ifndef _MAP_H
#define _MAP_H


enum GAMEOBJ
{
	G_WALL = '#',
	G_BOX = 'B',
	G_PORT = '@'
};

void mapData(char c[][60]);
void displayLevel();

void map1();
void map2();
void map3();
void map4();
void map5();
void map6();
void map7();
void map8();
void map9();
void map10();

#endif // _MAP_H