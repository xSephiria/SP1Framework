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

double timetaken;
string name;
void gettime() {

		std::cin >> name;
		switch (currentLevel)
			{
			case 1: saveHS1(); break; 
			case 2: saveHS2(); break;
			case 3: saveHS3(); break;
			case 4: saveHS4(); break;
			case 5: saveHS5(); break;
			case 6: saveHS6(); break;
			case 7: saveHS7(); break;
			case 8: saveHS8(); break;
			case 9: saveHS9(); break;
			case 10: saveHS10();; break;
			}

}


void saveHS1() {

	std::ofstream text;
	text.open("highscore1.txt",std::ofstream::out | std::ofstream::app);

	timetaken = g_dElapsedTime;

	text << name << "           " << timetaken << std::endl;

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

void saveHS2() {

	std::ofstream text;
	text.open("highscore2.txt",std::ofstream::out | std::ofstream::app);

	timetaken = g_dElapsedTime;

	text << name << "           " << timetaken << std::endl;

	text.close();

}

void saveHS3() {

	std::ofstream text;
	text.open("highscore3.txt",std::ofstream::out | std::ofstream::app);

	timetaken = g_dElapsedTime;

	text << name << "           " << timetaken << std::endl;

	text.close();

}

void saveHS4() {

	std::ofstream text;
	text.open("highscore4.txt",std::ofstream::out | std::ofstream::app);

	timetaken = g_dElapsedTime;

	text << name << "           " << timetaken << std::endl;

	text.close();

}

void saveHS5() {

	std::ofstream text;
	text.open("highscore5.txt",std::ofstream::out | std::ofstream::app);

	timetaken = g_dElapsedTime;

	text << name << "           " << timetaken << std::endl;

	text.close();

}

void saveHS6() {

	std::ofstream text;
	text.open("highscore6.txt",std::ofstream::out | std::ofstream::app);

	timetaken = g_dElapsedTime;

	text << name << "           " << timetaken << std::endl;

	text.close();

}

void saveHS7() {

	std::ofstream text;
	text.open("highscore7.txt",std::ofstream::out | std::ofstream::app);

	timetaken = g_dElapsedTime;

	text << name << "           " << timetaken << std::endl;

	text.close();

}

void saveHS8() {

	std::ofstream text;
	text.open("highscore8.txt",std::ofstream::out | std::ofstream::app);

	timetaken = g_dElapsedTime;

	text << name << "           " << timetaken << std::endl;

	text.close();

}

void saveHS9() {

	std::ofstream text;
	text.open("highscore9.txt",std::ofstream::out | std::ofstream::app);

	timetaken = g_dElapsedTime;

	text << name << "           " << timetaken << std::endl;

	text.close();

}

void saveHS10() {

	std::ofstream text;
	text.open("highscore10.txt",std::ofstream::out | std::ofstream::app);

	timetaken = g_dElapsedTime;

	text << name << "           " << timetaken << std::endl;

	text.close();

}

void readHS1() {

	g_Console.writeToBuffer(10, 0, "FASTEST TIMING FOR STAGE 1" ,0x04);
	g_Console.writeToBuffer(10, 1, "==========================" ,0x04);
	g_Console.writeToBuffer(10, 2, "NAME       |   TIMING" ,0x04);
	g_Console.writeToBuffer(10, 3, "==========================" ,0x04);

	std::string line;

    std::ifstream Reader ("highscore1.txt");             //Open file
 
	if (Reader.is_open())
	{
		int y = 4;
		while (getline (Reader, line))
		{
			line;
			g_Console.writeToBuffer(10, y, line);
			y++;
		}
		
	}
}

void readHS2() {

	g_Console.writeToBuffer(10, 0, "FASTEST TIMING FOR STAGE 2" ,0x04);
	g_Console.writeToBuffer(10, 1, "==========================" ,0x04);
	g_Console.writeToBuffer(10, 2, "NAME       |   TIMING" ,0x04);
	g_Console.writeToBuffer(10, 3, "==========================" ,0x04);

	std::string line;

    std::ifstream Reader ("highscore2.txt");             //Open file
 
	if (Reader.is_open())
	{
		int y = 4;
		while (getline (Reader, line))
		{
			line;
			g_Console.writeToBuffer(10, y, line);
			y++;
		}
		
	}
}

void readHS3() {

	g_Console.writeToBuffer(10, 0, "FASTEST TIMING FOR STAGE 3" ,0x04);
	g_Console.writeToBuffer(10, 1, "==========================" ,0x04);
	g_Console.writeToBuffer(10, 2, "NAME       |   TIMING" ,0x04);
	g_Console.writeToBuffer(10, 3, "==========================" ,0x04);

	std::string line;

    std::ifstream Reader ("highscore3.txt");             //Open file
 
	if (Reader.is_open())
	{
		int y = 4;
		while (getline (Reader, line))
		{
			line;
			g_Console.writeToBuffer(10, y, line);
			y++;
		}
		
	}
}

void readHS4() {

	g_Console.writeToBuffer(10, 0, "FASTEST TIMING FOR STAGE 4" ,0x04);
	g_Console.writeToBuffer(10, 1, "==========================" ,0x04);
	g_Console.writeToBuffer(10, 2, "NAME       |   TIMING" ,0x04);
	g_Console.writeToBuffer(10, 3, "==========================" ,0x04);

	std::string line;

    std::ifstream Reader ("highscore4.txt");             //Open file
 
	if (Reader.is_open())
	{
		int y = 4;
		while (getline (Reader, line))
		{
			line;
			g_Console.writeToBuffer(10, y, line);
			y++;
		}
		
	}
}

void readHS5() {

	g_Console.writeToBuffer(10, 0, "FASTEST TIMING FOR STAGE 5" ,0x04);
	g_Console.writeToBuffer(10, 1, "==========================" ,0x04);
	g_Console.writeToBuffer(10, 2, "NAME       |   TIMING" ,0x04);
	g_Console.writeToBuffer(10, 3, "==========================" ,0x04);

	std::string line;

    std::ifstream Reader ("highscore5.txt");             //Open file
 
	if (Reader.is_open())
	{
		int y = 4;
		while (getline (Reader, line))
		{
			line;
			g_Console.writeToBuffer(10, y, line);
			y++;
		}
		
	}
}

void readHS6() {

	g_Console.writeToBuffer(10, 0, "FASTEST TIMING FOR STAGE 6" ,0x04);
	g_Console.writeToBuffer(10, 1, "==========================" ,0x04);
	g_Console.writeToBuffer(10, 2, "NAME       |   TIMING" ,0x04);
	g_Console.writeToBuffer(10, 3, "==========================" ,0x04);

	std::string line;

    std::ifstream Reader ("highscore6.txt");             //Open file
 
	if (Reader.is_open())
	{
		int y = 4;
		while (getline (Reader, line))
		{
			line;
			g_Console.writeToBuffer(10, y, line);
			y++;
		}
		
	}
}

void readHS7() {

	g_Console.writeToBuffer(10, 0, "FASTEST TIMING FOR STAGE 7" ,0x04);
	g_Console.writeToBuffer(10, 1, "==========================" ,0x04);
	g_Console.writeToBuffer(10, 2, "NAME       |   TIMING" ,0x04);
	g_Console.writeToBuffer(10, 3, "==========================" ,0x04);

	std::string line;

    std::ifstream Reader ("highscore7.txt");             //Open file
 
	if (Reader.is_open())
	{
		int y = 4;
		while (getline (Reader, line))
		{
			line;
			g_Console.writeToBuffer(10, y, line);
			y++;
		}
		
	}
}

void readHS8() {

	g_Console.writeToBuffer(10, 0, "FASTEST TIMING FOR STAGE 8" ,0x04);
	g_Console.writeToBuffer(10, 1, "==========================" ,0x04);
	g_Console.writeToBuffer(10, 2, "NAME       |   TIMING" ,0x04);
	g_Console.writeToBuffer(10, 3, "==========================" ,0x04);

	std::string line;

    std::ifstream Reader ("highscore8.txt");             //Open file
 
	if (Reader.is_open())
	{
		int y = 4;
		while (getline (Reader, line))
		{
			line;
			g_Console.writeToBuffer(10, y, line);
			y++;
		}
		
	}
}

void readHS9() {

	g_Console.writeToBuffer(10, 0, "FASTEST TIMING FOR STAGE 9" ,0x04);
	g_Console.writeToBuffer(10, 1, "==========================" ,0x04);
	g_Console.writeToBuffer(10, 2, "NAME       |   TIMING" ,0x04);
	g_Console.writeToBuffer(10, 3, "==========================" ,0x04);

	std::string line;

    std::ifstream Reader ("highscore9.txt");             //Open file
 
	if (Reader.is_open())
	{
		int y = 4;
		while (getline (Reader, line))
		{
			line;
			g_Console.writeToBuffer(10, y, line);
			y++;
		}
		
	}
}

void readHS10() {

	g_Console.writeToBuffer(10, 0, "FASTEST TIMING FOR STAGE 10" ,0x04);
	g_Console.writeToBuffer(10, 1, "==========================" ,0x04);
	g_Console.writeToBuffer(10, 2, "NAME       |   TIMING" ,0x04);
	g_Console.writeToBuffer(10, 3, "==========================" ,0x04);

	std::string line;

    std::ifstream Reader ("highscore10.txt");             //Open file
 
	if (Reader.is_open())
	{
		int y = 4;
		while (getline (Reader, line))
		{
			line;
			g_Console.writeToBuffer(10, y, line);
			y++;
		}
		
	}
}