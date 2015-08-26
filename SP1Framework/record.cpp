#include "record.h"
#include "game.h"
#include "map.h"
#include "update.h"
#include "render.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>

extern int currentLevel;
extern Console g_Console;
extern double  g_dElapsedTime;
extern double  g_dDeltaTime;

double timetaken;
string name;
void gettime() {

		std::cin >> name;
		switch (currentLevel)
			{
			case 1: saveHS1(); break; 
			case 2: map2(); break;
			case 3: map3(); break;
			case 4: map4(); break;
			case 5: map5(); break;
			case 6: map6(); break;
			case 7: map7(); break;
			case 8: map8(); break;
			case 9: map9(); break;
			case 10: map10();; break;
			}

}


void saveHS1() {

	std::ofstream text;
	text.open("highscore1.txt",std::ofstream::out | std::ofstream::app);

	timetaken = g_dElapsedTime;

	text << name << " " << timetaken << std::endl;

	text.close();

}

void refreshtime () {

	COORD c;
	std::ostringstream ss;
	ss.str("");
    ss << g_dElapsedTime << "secs";
    c.X = g_Console.getConsoleSize().X - 15;
    c.Y = 9;
    g_Console.writeToBuffer(c, ss.str(), 0x59);

}

void readHS1() {

	std::ifstream text;
	text.open("highscore1.txt");

	/*if (text.fail()) {
		std::cerr << "ERROR" << std::endl;
		exit(1);
	}*/

	g_Console.writeToBuffer(0, 0, "FASTEST TIMING FOR STAGE 1" ,0x04);
	g_Console.writeToBuffer(0, 1, "==========================" ,0x04);
	g_Console.writeToBuffer(0, 2, "NAME       | TIMING" ,0x04);
	g_Console.writeToBuffer(0, 3, "==========================" ,0x04);

	//std::string line_;
	/*
	if (text.is_open())
	{
		while(getline(text,line_))
		{
			g_Console.writeToBuffer(0,4,line_,0x04);
		}
		text.close();
	}
	else
	{
		g_Console.writeToBuffer(0,5,"ERROR",0x04);
	}
	*/
	string name;
	string timing;
	while (true)
	{
		text >> name >> timing;
		if(text.eof()) break;
		g_Console.writeToBuffer(0,5,name,0x04);
	}

	
}