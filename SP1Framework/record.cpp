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
#include <conio.h>

extern bool g_abKeyPressed[K_COUNT];
extern int Health;
extern Console g_Console;
extern double  g_dElapsedTime;
extern double  g_dDeltaTime;
extern EGAMESTATES g_eGameState;
extern string PlayerName;
extern int &HSPointer;
extern int &LevelPointer;
string highscores[10] = {"Highscores/highscore1.txt","Highscores/highscore2.txt","Highscores/highscore3.txt","Highscores/highscore4.txt","Highscores/highscore5.txt","Highscores/highscore6.txt","Highscores/highscore7.txt","Highscores/highscore8.txt","Highscores/highscore9.txt","Highscores/highscore10.txt",};
string numbers[10] = {"1","2","3","4","5","6","7","8","9","10"};
int timetaken;
short data[10];
short bubble[12];


void gettime() {

		//std::cin >> name;

		std::fstream text;
		text.open(highscores[LevelPointer],std::fstream::in | std::fstream::out | std::fstream::app);

		timetaken = static_cast<int>(g_dElapsedTime);
		int score = 500;

		text << /*name << " " */ score - timetaken << std::endl;
		text.close();

		std::ifstream file;
		file.open(highscores[LevelPointer]);


		short line = 0;
		while (!file.eof())
		{
			file >> bubble[line];
		
			line++;
		}

		short temp;
		for(short i = line-1,j = line; i >= 0; i--, j--)
		{
			if (bubble[i] < bubble[j])
			{
	
				temp = bubble[i];
				bubble[i] = bubble[j];
				bubble[j] = temp;
			}
		}
		file.close();

	text.open(highscores[LevelPointer], std::ofstream::out | std::ofstream::trunc);
	text.close();

	text.open(highscores[LevelPointer], std::fstream::in | std::fstream::out);
	for (short i = 0 ; i < 10 ; i++)
	{
		data[i] = bubble[i];
		text << data[i] << std::endl;
	}
	text.close();
}
void readHS(int i)
{
	string word = "  TOP 10 FOR STAGE ";
	word += numbers[i];
	g_Console.writeToBuffer(1, 0, word ,0x0F);
	g_Console.writeToBuffer(1, 1, "======================" ,0x04);
	g_Console.writeToBuffer(1, 2, "        SCORE         " ,0x04);
	g_Console.writeToBuffer(1, 3, "======================" ,0x04);

	std::string line;
	std::string timing;
	std::string HP;

	/*std::ifstream file;
	file.open(highscores[i]);

	if(file.is_open()){

		std::ostringstream ss;
		for (int a = 0; a<10; a++)
		{
			if(data[a] == 0)
			{
				g_Console.writeToBuffer(27, 4+a, "-----");
			}
			else
			{
				ss.str("");
				ss << data[a] << "              " << Hdata[a];
				g_Console.writeToBuffer(27, 4+a, ss.str());
			}
		}
		ss.str("");
		g_Console.writeToBuffer(37, 2, ss.str());
	}

	file.close();*/

    std::ifstream Reader (highscores[i]);             //Open file

	if (Reader.is_open())
	{
		int y = 4;
		//insertsort(timing, line, HP);
		while (Reader >> timing)
		{
				g_Console.writeToBuffer(10, y, timing);
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
