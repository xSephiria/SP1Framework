#include "render.h"
#include "game.h"
#include "Framework\console.h"

extern Console g_Console;
extern int &MenuPointer;
extern int &LevelPointer;
extern int &OptionsPointer;
extern int &CharPointer;
void renderMainMenu()
{
	string Menu[4] ={"                                   Start Game","                                  Instructions", "                                    Options", "                                      Exit"};
	char box[9][75] = {
"                  ______   _______           _______  _______ ",
"                 (  ___ \\ (  ___  )|\\     /|(  ____ \\(  ____ \\",
"                 | (   ) )| (   ) |( \\   / )| (    \\/| (    \\/",
"                 | (__/ / | |   | | \\ (_) / | (__    | (_____ ",
"                 |  __ (  | |   | |  ) _ (  |  __)   (_____  )",
"                 | (  \\ \\ | |   | | / ( ) \\ | (            ) |",
"                 | )___) )| (___) |( /   \\ )| (____/\\/\\____) |",
"                 |______/ (_______)|/     \\|(_______/\\_______)"
	};
  for (int i = 0; i < 9; i++)
  {
  g_Console.writeToBuffer(0,i,box[i],0x02);
  }
  for (int i = 0; i < 4; ++i)
		{
			if (i == MenuPointer)
			{	
				 g_Console.writeToBuffer(0,10+i,Menu[i],0x0B);
			}
			else
			{
				 g_Console.writeToBuffer(0,10+i,Menu[i],0x03);
			}
		}
}
void renderLevelMenu()
{
	string Menu[11] ={"                                      Map1",
		              "                                      Map2", 
					  "                                      Map3", 
					  "                                      Map4", 
					  "                                      Map5", 
					  "                                      Map6", 
					  "                                      Map7", 
					  "                                      Map8", 
					  "                                      Map9",
					  "                                      Map10",
					  "                               Back to Main Menu"};

	g_Console.writeToBuffer(31,2,"Choose Your Level",0x04);

	for (int i = 0; i < 11; ++i)
		{
			if (i == LevelPointer)
			{
				g_Console.writeToBuffer(0, 6+i,Menu[i],0x0B);
			}
			else
			{
				g_Console.writeToBuffer(0, 6+i,Menu[i],0x03);
			}
		}
}
void renderOptionsMenu()
{
	string Options[3] ={"Character", "Something", "Back To Main Menu"};
	g_Console.writeToBuffer(36,2,"OPTIONS",0x04);
	for (int i = 0; i < 3; ++i)
		{
			if (i == OptionsPointer)
			{	
				 g_Console.writeToBuffer(35,10+i,Options[i],0x0B);
			}
			else
			{
				 g_Console.writeToBuffer(35,10+i,Options[i],0x03);
			}
		}
}
void renderInstruct()
{
	g_Console.writeToBuffer(17, 5, "Controls" , 0x0B );
	g_Console.writeToBuffer(17, 6, "Arrow Key Up = Move up" );
	g_Console.writeToBuffer(17, 7, "Arrow Key Down = Move down" );
	g_Console.writeToBuffer(17, 8, "Arrow Key Left = Move left" );
	g_Console.writeToBuffer(17, 9, "Arrow Key Right = Move right" );
	g_Console.writeToBuffer(17, 10, "Spacebar = Restart stage");
	g_Console.writeToBuffer(17, 11, "Backspace = Return to previous menu");
	g_Console.writeToBuffer(17, 12, "Esc = Quit game");

	g_Console.writeToBuffer(17, 14, "Backstory" , 0x0B);
	g_Console.writeToBuffer(17, 15, "A man went into a cave to train by pushing boxes.");
	g_Console.writeToBuffer(17, 16, "However,the more he pushed, the more he got addicted.");
	g_Console.writeToBuffer(17, 17, "This left him getting stuck in the cave building his");
	g_Console.writeToBuffer(17, 18, "biceps for years. All hope is not lost yet, it seems");
	g_Console.writeToBuffer(17, 19, "that if he gets to a portal, he might just get out!?");

	g_Console.writeToBuffer(17, 21, "Press backspace to return" , 0x0B );
}
void renderCharSelect() {

	g_Console.writeToBuffer(27,8," Select Your Character ",0x0B);
	char Char[4] ={(char)255,(char)1,(char)2,(char)3,};
	string CharName[4] ={"Stealth","HollowFace", "FullFace", "HeartShape"};
	g_Console.writeToBuffer(33,10," << ",0x0B);
	for (int i = 0; i < 4; ++i)
		{
			if (i == CharPointer)
			{	
				 g_Console.writeToBuffer(38,10,Char[i],0x0B);
				 g_Console.writeToBuffer(35,11,CharName[i],0x0B);
			}
			else
			{
				 Char[i];
				 CharName[i];
			}
		}
	g_Console.writeToBuffer(40,10," >> ",0x0B);
}
