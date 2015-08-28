#include "render.h"
#include "record.h"
#include "game.h"
#include "Framework\console.h"

extern Console g_Console;
extern int &MenuPointer;
extern int &LevelPointer;
extern int &OptionsPointer;
extern int &CharPointer;
extern int &HSPointer;
void renderMainMenu()
{
	string Menu[4] ={"Start Game","Instructions", "Options", "Exit"};
	char box[9][75] = {
" ______   _______           _______  _______ ",
"(  ___ \\ (  ___  )|\\     /|(  ____ \\(  ____ \\",
"| (   ) )| (   ) |( \\   / )| (    \\/| (    \\/",
"| (__/ / | |   | | \\ (_) / | (__    | (_____ ",
"|  __ (  | |   | |  ) _ (  |  __)   (_____  )",
"| (  \\ \\ | |   | | / ( ) \\ | (            ) |",
"| )___) )| (___) |( /   \\ )| (____/\\/\\____) |",
"|______/ (_______)|/     \\|(_______/\\_______)"
	};
  for (int i = 0; i < 9; i++)
  {
  g_Console.writeToBuffer(17,i,box[i],0x02);
  }
  for (int i = 0; i < 4; ++i)
		{
			if (i == MenuPointer)
			{	
				 g_Console.writeToBuffer(35,10+i,Menu[i],0x0B);
			}
			else
			{
				 g_Console.writeToBuffer(35,10+i,Menu[i],0x03);
			}
		}
}
void renderLevelMenu()
{
	string Menu[11] ={"Map1",
		              "Map2", 
					  "Map3", 
					  "Map4", 
					  "Map5", 
					  "Map6", 
					  "Map7", 
					  "Map8", 
					  "Map9",
					  "Map10",
					  "Return"};

	g_Console.writeToBuffer(31,2,"Choose Your Level",0x04);

	for (int i = 0; i < 11; ++i)
		{
			if (i == LevelPointer)
			{
				g_Console.writeToBuffer(39, 6+i,Menu[i],0x0B);
			}
			else
			{
				g_Console.writeToBuffer(39, 6+i,Menu[i],0x03);
			}
		}

}
void renderOptionsMenu()
{
	string Options[3] ={"Character", "Highscores", "Back To Main Menu"};
	g_Console.writeToBuffer(37,2,"OPTIONS",0x04);
	for (int i = 0; i < 3; ++i)
		{
			if (i == OptionsPointer)
			{	
				 g_Console.writeToBuffer(37,10+i,Options[i],0x0B);
			}
			else
			{
				 g_Console.writeToBuffer(37,10+i,Options[i],0x03);
			}
		}
}
void renderInstruct()
{
	readtext();
}
void renderCharSelect() {

	g_Console.writeToBuffer(27,8," Select Your Character ",0x0B);
	char Char[4] ={(char)255,(char)1,(char)2,(char)3,};
	string CharName[4] ={"Stealth","HollowFace", "FullFace", "HeartShape"};
	g_Console.writeToBuffer(33,10," << ",0x0B);
	
	g_Console.writeToBuffer(38,10,Char[CharPointer],0x0B);
	g_Console.writeToBuffer(35,11,CharName[CharPointer],0x0B);
	
	g_Console.writeToBuffer(40,10," >> ",0x0B);
}
void renderHSMenu()
{
	string HS[11] = {"Map 1","Map 2","Map 3","Map 4","Map 5","Map 6","Map 7","Map 8","Map 9","Map 10","Return"};
	g_Console.writeToBuffer(37,2,"HIGHSCORES",0x04);
	for (int i = 0; i < 11; ++i)
		{
			if (i == HSPointer)
			{	
				 g_Console.writeToBuffer(39,6+i,HS[i],0x0B);
			}
			else
			{
				 g_Console.writeToBuffer(39,6+i,HS[i],0x03);
			}
		}
}

void readtext()
{
	std::string line;
 
    std::ifstream Reader ("Instructions.txt");             //Open file
 
	if (Reader.is_open())
	{
		int y = 3;
		while (getline (Reader, line))
		{
			line;
			g_Console.writeToBuffer(7, y, line);
			y++;
		}
		
	}
	Reader.close();
}