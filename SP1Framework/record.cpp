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
#include <algorithm>
#include <vector>

extern int currentLevel;
extern Console g_Console;
extern double  g_dElapsedTime;
extern double  g_dDeltaTime;

string highscores[11] = {"","Highscores/highscore1.txt","Highscores/highscore2.txt","Highscores/highscore3.txt","Highscores/highscore4.txt","Highscores/highscore5.txt","Highscores/highscore6.txt","Highscores/highscore7.txt","Highscores/highscore8.txt","Highscores/highscore9.txt","Highscores/highscore10.txt",};
string numbers[11] = {"","1","2","3","4","5","6","7","8","9","10"};
double timetaken;
string name;
void gettime() {

		std::cin >> name;
		std::ofstream text;
		text.open(highscores[currentLevel],std::ofstream::out | std::ofstream::app);

		timetaken = g_dElapsedTime;

		text << name << "           " << timetaken << std::endl;
		
		text.close();

}
void readHS()
{
	string word = "FASTEST TIMING FOR STAGE ";
	word += numbers[currentLevel];
	g_Console.writeToBuffer(10, 0, word ,0x0F);
	g_Console.writeToBuffer(10, 1, "==========================" ,0x04);
	g_Console.writeToBuffer(10, 2, "NAME       |   TIMING" ,0x04);
	g_Console.writeToBuffer(10, 3, "==========================" ,0x04);

	std::string line;
	std::string timing;
    std::ifstream Reader (highscores[currentLevel]);             //Open file

	if (Reader.is_open())
	{
		int y = 4;
		while (Reader >> line >> timing)
		{
			line;
			g_Console.writeToBuffer(10, y, line);
			g_Console.writeToBuffer(25, y, timing);
			y++;
		}
		
	}
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

