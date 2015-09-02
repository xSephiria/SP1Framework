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
int HP;
string name;
short times[10];
short data[10];
short Hdata[10];
short bubble[12];
short health[12];

void gettime() {

		//std::cin >> name;

		std::fstream text;
		text.open(highscores[LevelPointer],std::fstream::in | std::fstream::out | std::fstream::app);

		timetaken = static_cast<int>(g_dElapsedTime);
		HP = static_cast<int>(Health);
		int score = 500;

		text << /*name << " " */ score - timetaken << " " << HP << std::endl;
		text.close();

		std::ifstream file;
		file.open(highscores[LevelPointer]);


		short line = 0;
		while (!file.eof())
		{
			file >> bubble[line] >> health[line];
		
			line++;
		}

		short temp;
		short Htemp;
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
		Hdata[i] = health[i];
		text << data[i] << " " << Hdata[i]<< std::endl;
	}
	text.close();

	g_eGameState = S_LEVELMENU;

}
void readHS(int i)
{
	string word = "RECORDED SCORE FOR STAGE ";
	word += numbers[i];
	g_Console.writeToBuffer(10, 0, word ,0x0F);
	g_Console.writeToBuffer(10, 1, "==============================================" ,0x04);
	g_Console.writeToBuffer(10, 2, "SCORE" ,0x04);
	g_Console.writeToBuffer(10, 3, "==============================================" ,0x04);

	std::string line;
	std::string timing;
	std::string HP;


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

    /*std::ifstream Reader (highscores[i]);             //Open file

	if (Reader.is_open())
	{
		int y = 4;

		//insertsort(timing, line, HP);
		while (Reader >> timing)
		{
				g_Console.writeToBuffer(27, y, timing);
				y++;
		}
	}

	Reader.close();*/
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

	if (g_abKeyPressed[K_RETURN])
	{
				g_eGameState = S_LEVELMENU;
	}

}


/*void insertsort(std::string time[],std::string line[],std::string HP[]){

	std::string tempt;
	std::string tempn;
	std::string temph;
	std::string times;
	std::string names;
	std::string health;
	int j = 0;
	int i = 0;
	int num = 10;

	 std::fstream Reader;//Open file
	 Reader.open(highscores[HSPointer], std::ios::in | std::ios::out);     


	 while(!Reader.eof() && i < num)
	 {
		 Reader >> *line >> *time >> *HP;
		 time[i] = times;
		 line[i] = names;
		 HP[i] = health;
	/* {
		for (int i = 1; i < num; i++)
		{
		time[i] = tempt;
		line[i] = tempn;
		HP[i] = temph;

		j = i;
			while( j > 0 && time[j] < time[j-1])
			{
				tempt = time[j];
				time[j] = time[j - 1];
				time[j-1] = tempt;
				temph = HP[j];
				HP[j] = HP[j - 1];
				HP[j-1] = tempt;
				tempn = line[j];
				line[j] = line[j - 1];
				line[j-1] = tempn;
				j--;
			}
			i++;
	}
	Reader.close();
}*/

