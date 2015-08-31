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

extern int Health;
extern Console g_Console;
extern double  g_dElapsedTime;
extern double  g_dDeltaTime;
extern EGAMESTATES g_eGameState;
extern string PlayerName;
extern int &HSPointer;
string highscores[10] = {"Highscores/highscore1.txt","Highscores/highscore2.txt","Highscores/highscore3.txt","Highscores/highscore4.txt","Highscores/highscore5.txt","Highscores/highscore6.txt","Highscores/highscore7.txt","Highscores/highscore8.txt","Highscores/highscore9.txt","Highscores/highscore10.txt",};
string numbers[10] = {"1","2","3","4","5","6","7","8","9","10"};
double timetaken;
double HP;
string name;

void gettime() {

		cls();
		std::cin >> name;

		std::ofstream text;
		text.open(highscores[HSPointer],std::ofstream::out | std::ofstream::app);

		timetaken = g_dElapsedTime;
		HP = Health;

		text << name << " " << timetaken << " " << HP << std::endl;
		
		text.close();

		g_eGameState = S_LEVELMENU;

}
void readHS(int i)
{
	string word = "RECORDED TIMING FOR STAGE ";
	word += numbers[i];
	g_Console.writeToBuffer(10, 0, word ,0x0F);
	g_Console.writeToBuffer(10, 1, "==============================================" ,0x04);
	g_Console.writeToBuffer(10, 2, "NAME       |     TIMING      | Life Remaining " ,0x04);
	g_Console.writeToBuffer(10, 3, "==============================================" ,0x04);

	std::string line;
	std::string timing;
	std::string HP;
    std::ifstream Reader (highscores[i]);             //Open file

	if (Reader.is_open())
	{
		int y = 4;
		while (Reader >> line >> timing >> HP)
		{
			line;
			g_Console.writeToBuffer(10, y, line);
			g_Console.writeToBuffer(27, y, timing);
			g_Console.writeToBuffer(48, y, HP);
			y++;
		}
		
	}
	Reader.close();
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

void keyname() {

	g_Console.writeToBuffer(15,6, " ____________________________________________ ", 0x04);
	g_Console.writeToBuffer(15,7, "|                                            |", 0x04);
	g_Console.writeToBuffer(15,8, "|               CONGRATULATION!              |", 0x04);
	g_Console.writeToBuffer(15,9, "|           YOU CLEARED THIS STAGE!          |", 0x04);
	g_Console.writeToBuffer(15,10, "|                                            |", 0x04);
	g_Console.writeToBuffer(15,11, "|           YOUR NAME:                       |", 0x04);
	g_Console.writeToBuffer(15,12, "|                                            |", 0x04);
	g_Console.writeToBuffer(15,13, "|                                            |", 0x04);
	g_Console.writeToBuffer(15,14, "|____________________________________________|", 0x04);
}
