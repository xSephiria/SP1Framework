// This is the main file to hold everthing together

#include "Framework\timer.h"
#include "game.h"
#include <string>
#include <windows.h>
#include <iostream>

using std::string;
using std::cout;
using std::endl;


StopWatch g_timer;            // Timer function to keep track of time and the frame rate
bool something = false;
bool g_quitGame = false;      // Set to true if you want to quit the game
const unsigned char FPS = 10; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame

int displayMenu();
int levelMenu();
int optionsMenu();
void gameStart();
int currentLevel;


void mainLoop();

// TODO:
// Bug in waitUnitil. it waits for the time from getElapsedTime to waitUntil, but should be insignificant.

int main()
{
	init();      // initialize your variables
    mainLoop();  // main loop
    shutdown();  // do clean up, if any. free memory.
	
	return 0;
}

// This main loop calls functions to get input, update and render the game
// at a specific frame rate
void mainLoop()
{
    g_timer.startTimer(); // Start timer to calculate how long it takes to render this frame
	displayMenu();    
}
int displayMenu()
{
	string Menu[3] ={"                                   Start Game", "                                    Options", "                                      Exit"};
	int pointer = 0;

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
	
	while(!something)
	{
		system("cls");

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			for ( int i = 0; i < 9; i++)
			{
			cout << box[i] << endl;
			}

		for (int i = 0; i < 3; ++i)
		{
			if (i == pointer)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				cout << Menu[i] << endl;
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << Menu[i] << endl;
			}
	}

		while(!something)
		{
			if (GetAsyncKeyState(VK_UP) != 0)
			{
				pointer -= 1;
				if (pointer == -1)
				{
					pointer = 2;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_DOWN) != 0)
			{
				pointer += 1;
				if (pointer == 3)
				{
					pointer = 0;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_RETURN) != 0)
			{
				switch(pointer)
				{

					case 0:
						{
							levelMenu();
						}break;
					case 1: 
						{
							optionsMenu();
						}break;
					case 2:
						{
							something = true;
						}break;
				}

			}
			break;
			
		}
		Sleep(150);
		
	}
	return 0;
}

int levelMenu()
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
					  "                                      Map10\n\n",
					  "                               Back to Main Menu"};
	int pointer = 0;

	while(!something)
	{
		system("cls");

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			cout << "                               Choose Your Level\n\n\n\n";

		for (int i = 0; i < 11; ++i)
		{
			if (i == pointer)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				cout << Menu[i] << endl;
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << Menu[i] << endl;
			}
	}

		while(!something)
		{
			if (GetAsyncKeyState(VK_UP) != 0)
			{
				pointer -= 1;
				if (pointer == -1)
				{
					pointer = 10;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_DOWN) != 0)
			{
				pointer += 1;
				if (pointer == 11)
				{
					pointer = 0;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_RETURN) != 0)
			{
				g_quitGame = false;
				switch(pointer)
				{

					case 0:
						{
							currentLevel = 1;
							gameStart();  //Map 1
							
						}break;
					case 1: 
						{
							currentLevel = 2;
							gameStart(); //Map 2
						}break;
					case 2:
						{
							currentLevel = 3;
							gameStart(); //Map 3
						}break;
					case 3:
						{
							currentLevel = 4;
							gameStart(); //Map 4
						}break;
					case 4:
						{
							currentLevel = 5;
							gameStart(); //Map 5
						}break;
					case 5:
						{
							currentLevel = 6;
							gameStart(); //Map 6
						}break;
					case 6:
						{
							currentLevel = 7;
							gameStart(); //Map 7
						}break;
					case 7:
						{
							currentLevel = 8;
							gameStart(); //Map 8
						}break;
					case 8:
						{
							currentLevel = 9;
							gameStart(); //Map 9
						}break;
					case 9:
						{
							currentLevel = 10;
							gameStart(); //Map 10
						}break;
					case 10:
						{
							displayMenu();
						}break;
				}

			}
			break;
			
		}
		Sleep(150);
		
	}
	return 0;
}

int optionsMenu()
{
	string Menu[3] ={"Speed Mod", "Change Color", "Back to Main Menu"};
	int pointer = 0;

	while(!something)
	{
		system("cls");

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			cout << "Options\n\n";

		for (int i = 0; i < 3; ++i)
		{
			if (i == pointer)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				cout << Menu[i] << endl;
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << Menu[i] << endl;
			}
	}

		while(!something)
		{
			if (GetAsyncKeyState(VK_UP) != 0)
			{
				pointer -= 1;
				if (pointer == -1)
				{
					pointer = 2;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_DOWN) != 0)
			{
				pointer += 1;
				if (pointer == 3)
				{
					pointer = 0;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_RETURN) != 0)
			{
				switch(pointer)
				{

					case 0:
						{
							cout << "\n\nThis should be SpeedMod Option";
						}break;
					case 1:
						{
							cout <<"\n\nThis sould be ColorChange Option";
						}break;
					case 2:
						{
							return 0;
						}break;
				}
			}
			break;
			
		}
		Sleep(150);
		
	}
	return 0;
}
void displayLevel()
{
	switch (currentLevel)
	{
	case 1: map1(); break;
	case 2: map2(); break;
	case 3: map3(); break;
	case 4: map4(); break;
	case 5: map5(); break;
	case 6: map6(); break;
	case 7: map7(); break;
	case 8: map8(); break;
	case 9: map9(); break;
	case 10: map10(); break;
	}
}
void gameStart()
{
	displayLevel();

	 while (!g_quitGame)      // run this loop until user wants to quit 
	{        
        getInput();                         // get keyboard input
        update(g_timer.getElapsedTime());   // update the game
        render();                           // render the graphics output to screen
        g_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.      
	}
}

