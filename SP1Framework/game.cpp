// This is the main file for the game logic and function
//
//
#include "game.h"
#include "map.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

using std::string;

double  g_dElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];

bool something = false;

int currentLevel;           // Current Level ~.~

int MenuP = 0;              // "Cursors" for main menu
int &MenuPointer = MenuP;
int LevelP = 0;               // "Cursors" for level menu
int &LevelPointer = LevelP;
int OptionsP = 0;
int &OptionsPointer = OptionsP;
int Health = 3;
// Game specific variables here
SGameChar   g_sChar;
EGAMESTATES g_eGameState = S_MAINMENU;
double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once

int x = g_sChar.m_cLocation.X;
int y = g_sChar.m_cLocation.Y;
// Console object
Console g_Console(79, 28, "SP1 Framework");

extern char map[25][60];
int playSong()
{
	PlaySound(TEXT("freesong.wav"), NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);		
	return 0;
}
//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init( void )
{
	playSong();
    // Set precision for floating point output
    g_dElapsedTime = 0.0;
    g_dBounceTime = 0.0;

    // sets the initial state for the game
    g_eGameState = S_MAINMENU;

    g_sChar.m_cLocation.X = 28;
    g_sChar.m_cLocation.Y = 16;
    g_sChar.m_bActive = true;
    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 36, L"Calibri");
}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void shutdown( void )
{
    // Reset to white text on black background
    colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    g_Console.clearBuffer();
}

//--------------------------------------------------------------
// Purpose  : Getting all the key press states
//            This function checks if any key had been pressed since the last time we checked
//            If a key is pressed, the value for that particular key will be true
//
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void getInput( void )
{    
    g_abKeyPressed[K_UP]     = isKeyPressed(VK_UP);
    g_abKeyPressed[K_DOWN]   = isKeyPressed(VK_DOWN);
    g_abKeyPressed[K_LEFT]   = isKeyPressed(VK_LEFT);
    g_abKeyPressed[K_RIGHT]  = isKeyPressed(VK_RIGHT);
    g_abKeyPressed[K_SPACE]  = isKeyPressed(VK_SPACE);
    g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	g_abKeyPressed[K_BACK]   = isKeyPressed(VK_BACK);
	g_abKeyPressed[K_RETURN] = isKeyPressed(VK_RETURN);
}

//--------------------------------------------------------------
// Purpose  : Update function
//            This is the update function
//            double dt - This is the amount of time in seconds since the previous call was made
//
//            Game logic should be done here.
//            Such as collision checks, determining the position of your game characters, status updates, etc
//            If there are any calls to write to the console here, then you are doing it wrong.
//
//            If your game has multiple states, you should determine the current state, and call the relevant function here.
//
// Input    : dt = deltatime
// Output   : void
//--------------------------------------------------------------
void update(double dt)
{
    // get the delta time
    g_dElapsedTime += dt;
    g_dDeltaTime = dt;
	
    switch (g_eGameState)
    {
        case S_MAINMENU : updateMenu(); // game logic for the splash screen
            break;
		case S_INSTRUCTIONS: updateInstruct(); // game logic for instructions
			break;
        case S_GAME: gameplay();  // gameplay logic when we are in the game
            break;
		case S_LEVELMENU : updateLevelMenu(); //Level Menu
			break;
		case S_OPTIONS : updateOptionsMenu();
			break;
    }
	
}
//--------------------------------------------------------------
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// Output   : void
//--------------------------------------------------------------
void render()
{
    clearScreen();     // clears the current screen and draw from scratch 
    switch (g_eGameState)
    {
        case S_MAINMENU: renderMainMenu();
            break;
		case S_INSTRUCTIONS: renderInstruct();
			break;
        case S_GAME: renderGame();
            break;
		case S_LEVELMENU : renderLevelMenu(); 
			break;
		case S_OPTIONS : renderOptionsMenu();
			break;
    }
	
	    renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
}
/*void splashScreenWait()    // waits for time to pass in splash screen
{
    if (g_dElapsedTime > 5.0) // wait for 3 seconds to switch to game mode, else do nothing
        g_eGameState = S_GAME;
}*/

void gameplay()            // gameplay logic
{
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter();    // moves the character, collision detection, physics, etc
                        // sound can be played here too.
	
}

void moveCharacter()
{
    bool bSomethingHappened = false;
    if (g_dBounceTime > g_dElapsedTime)
        return;

	int x = g_sChar.m_cLocation.X;
	int y = g_sChar.m_cLocation.Y;

    // Updating the location of the character based on the key press
    // providing a beep sound whenver we shift the character
    if (g_abKeyPressed[K_UP] && g_sChar.m_cLocation.Y > 0)
    {
        if (map[y-1][x] != (char)178)
	   {
			if( map[y - 1][x] != (char)177) //if box not present
			{ 
                g_sChar.m_cLocation.Y--;
				
			} 
			else if ( map[y - 1][x] == (char)177 && map[y-2][x] != (char)178 && map[y-2][x] != (char)177)
			{
				map[y - 2][x] = (char)177;
				g_sChar.m_cLocation.Y--;
				map[y - 1][x] = ' ';
				
			}
			else if (map[y-1][x] != (char)177 && map[y-2][x] != (char)177 )
			{
				g_sChar.m_cLocation.Y--;
			}
		}
        bSomethingHappened = true;
    }
    else if (g_abKeyPressed[K_LEFT] && g_sChar.m_cLocation.X > 0)
    {
        if (map[y][x-1] != (char)178)
	    {
			if( map[y][x-1] != (char)177) //if box(ascii char 66) not present
			{ 
                g_sChar.m_cLocation.X--;	
			} 
			else if ( map[y][x-1] == (char)177 && map[y][x-2] != (char)178 && map[y][x-2] != (char)177)
			{
				map[y][x-2] = (char)177;
				g_sChar.m_cLocation.X--;
				map[y][x-1] = ' ';	
			}
			else if (map[y][x-1] != (char)177 && map[y][x-2] != (char)177 )
			{
				g_sChar.m_cLocation.X--;
			}
		}
        bSomethingHappened = true;
    }
    else if (g_abKeyPressed[K_DOWN] && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
    {
       if (map[y+1][x] != (char)178)
	   {
			if( map[y + 1][x] != (char)177) //if box(ascii char 66) not present
			{ 
                g_sChar.m_cLocation.Y++;
			} 
			else if ( map[y+1][x] == (char)177 && map[y+2][x] != (char)178 && map[y+2][x] != (char)177)
			{
				map[y+2][x] = (char)177;
				g_sChar.m_cLocation.Y++;
				map[y+1][x] = ' ';
			
			}
			else if (map[y+1][x] != (char)177 && map[y+2][x] != (char)177 )
			{
				g_sChar.m_cLocation.Y++;
			}
		}
        bSomethingHappened = true;
    }
    else if (g_abKeyPressed[K_RIGHT] && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
    {
       if (map[y][x+1] != (char)178)
	    {
			if( map[y][x+1] != (char)177) //if box(ascii char 66) not present
			{ 
                g_sChar.m_cLocation.X++;
			} 
			else if ( map[y][x+1] == (char)177 && map[y][x+2] != (char)178 && map[y][x+2] != (char)177)
			{
				map[y][x+2] = (char)177;
				g_sChar.m_cLocation.X++;
				map[y][x+1] = ' ';
			}
			else if (map[y][x+1] != (char)177 && map[y][x+2] != (char)177 )
			{
				g_sChar.m_cLocation.X++;
			}
        bSomethingHappened = true;
		}
	}
	if (map[y][x] == '@')
	{
		g_sChar.m_cLocation.X = 28;
		g_sChar.m_cLocation.Y = 16;
		g_eGameState = S_LEVELMENU;
		//displayLevel();
		bSomethingHappened = true;
	}

    if (bSomethingHappened)
    {
        // set the bounce time to some time in the future to prevent accidental triggers
        g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
    }
}
void processUserInput()
{
	bool bSomethingHappened = false;
    if (g_dBounceTime > g_dElapsedTime)
        return;
<<<<<<< 3867a93adb5586dddbc72cd73ebae4a8628207c0

=======
>>>>>>> 0694aca494e2078196e0242319bad101b1182e16
    // quits the game if player hits the escape key
    if (g_abKeyPressed[K_ESCAPE])
        g_bQuitGame = true; 
	else if (g_abKeyPressed[K_SPACE])
    {
		bSomethingHappened = true;
        g_sChar.m_cLocation.X = 28;
		g_sChar.m_cLocation.Y = 16;
		displayLevel();
		loselife();
		bSomethingHappened = true;
    }
	else if (g_eGameState == S_GAME && GetAsyncKeyState(VK_BACK) != 0)
	{
		bSomethingHappened = true;
		g_sChar.m_cLocation.X = 28;
		g_sChar.m_cLocation.Y = 16;
		g_eGameState = S_LEVELMENU;
		bSomethingHappened = true;
	}
<<<<<<< 3867a93adb5586dddbc72cd73ebae4a8628207c0
=======

>>>>>>> 0694aca494e2078196e0242319bad101b1182e16
	if (bSomethingHappened)
    {
        // set the bounce time to some time in the future to prevent accidental triggers
        g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
    }
}

void clearScreen()
{
    // Clears the buffer with this colour attribute
    g_Console.clearBuffer(0x0F);
}
void renderGame()
{
    renderMap();        // renders the map to the buffer first
    renderCharacter();  // renders the character into the buffer
	lifepoint();
	renderFramerate();  // renders debug information, frame rate, elapsed time, etc
}
void renderMap()
{
    // Set up sample colours, and output shadings
    /*const WORD colors[] = {
        0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
    };

    COORD c;
    for (int i = 0; i < 12; ++i)
    {
        c.X = 5 * i;
        c.Y = i + 1;
        colour(colors[i]);
        g_Console.writeToBuffer(c, " °±²Û", colors[i]);
    }*/

	for(int i = 0; i < 25; i++) 
	{
		for (int j = 0; j < 60; j++)
		{
			if (map[i][j] == (char)178)
			{
				g_Console.writeToBuffer(j,i,map[i][j],0x0B);
			}
			else if (map[i][j] == (char)177)
			{
				g_Console.writeToBuffer(j,i,map[i][j],0x0E);
			}
			else
				g_Console.writeToBuffer(j,i,map[i][j],0x0F);
		
		}
	}



}

void renderCharacter()
{
    // Draw the location of the character
    WORD charColor = 0x0C;
    /*if (g_sChar.m_bActive)
    {
        charColor = 0x0A;
    }*/
    g_Console.writeToBuffer(g_sChar.m_cLocation, (char)3, charColor);
}
void renderFramerate()
{
    COORD c;
    // displays the framerate
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(3);
    ss << 1.0 / g_dDeltaTime << "fps";
    c.X = g_Console.getConsoleSize().X - 15;
    c.Y = 10;
    g_Console.writeToBuffer(c, ss.str());

    // displays the elapsed time
    ss.str("");
    ss << g_dElapsedTime << "secs";
    c.X = g_Console.getConsoleSize().X - 15;
    c.Y = 9;
    g_Console.writeToBuffer(c, ss.str(), 0x59);



}
void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
}
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

	g_Console.writeToBuffer(0,2,"                               Choose Your Level",0x04);

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
	string Options[3] ={"                                   Something", "                                   Something", "                               Back To Main Menu"};
	g_Console.writeToBuffer(0,2,"                                    OPTIONS",0x04);
	for (int i = 0; i < 3; ++i)
		{
			if (i == OptionsPointer)
			{	
				 g_Console.writeToBuffer(0,10+i,Options[i],0x0B);
			}
			else
			{
				 g_Console.writeToBuffer(0,10+i,Options[i],0x03);
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

void updateMenu()
{
	bool bSomethingHappened = false;
    if (g_dBounceTime > g_dElapsedTime)
        return;
	if (g_abKeyPressed[K_UP])
			{
				bSomethingHappened = true;
				MenuPointer--;
				if (MenuPointer == -1)
				{
					MenuPointer = 3;
				}
			}
			else if (g_abKeyPressed[K_DOWN])
			{
				bSomethingHappened = true;
				MenuPointer++;
				if (MenuPointer == 4)
				{
					MenuPointer = 0;
				}
			}
			else if (g_abKeyPressed[K_RETURN])
			{
				bSomethingHappened = true;
				switch(MenuPointer)
				{

					case 0:
						{
							g_eGameState = S_LEVELMENU; 
						}break;
					case 1:
						{
							g_eGameState = S_INSTRUCTIONS;
						}break;
					case 2: 
						{
							g_eGameState = S_OPTIONS;
						}break;
					case 3:
						{
							g_bQuitGame = true;
						}break;
				}
			}

			else if (g_abKeyPressed[K_ESCAPE])
			{
				g_bQuitGame = true;
			}
			if (bSomethingHappened)
			 {
				// set the bounce time to some time in the future to prevent accidental triggers
				g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
			 }
}
void updateLevelMenu()
{
	bool bSomethingHappened = false;
    if (g_dBounceTime > g_dElapsedTime)
        return;
	if (g_abKeyPressed[K_UP])
			{
				bSomethingHappened = true;
				LevelPointer -= 1;
				if (LevelPointer == -1)
				{
					LevelPointer = 10;
				}
			}
	else if (g_abKeyPressed[K_DOWN])
			{
				bSomethingHappened = true;
				LevelPointer += 1;
				if (LevelPointer == 11)
				{
					LevelPointer = 0;
				}
			}
	else if (g_abKeyPressed[K_RETURN])
			{
				bSomethingHappened= true;
				g_bQuitGame = false;
				switch(LevelPointer)
				{
					case 0:
						{
							currentLevel = 1;//Map1
							Health = 3;
							displayLevel();
							g_eGameState = S_GAME;
							break;
						}
					case 1:
						{
							currentLevel = 2;//Map2
							Health = 3;
							displayLevel();
							g_eGameState = S_GAME;
							break;
						}
					case 2:
						{
							currentLevel = 3;//Map3
							Health = 3;
							displayLevel();
							g_eGameState = S_GAME;
							break;
						}
					case 3:
						{
							currentLevel = 4;//Map4
							Health = 3;
							displayLevel();
							g_eGameState = S_GAME;
							break;
						}
					case 4:
						{
							currentLevel = 5;//Map5
							Health = 3;
							displayLevel();
							g_eGameState = S_GAME;
							break;
						}
					case 5:
						{
							currentLevel = 6;//Map6
							Health = 3;
							displayLevel();
							g_eGameState = S_GAME;
							break;
						}
					case 6:
						{
							currentLevel = 7;//Map7
							Health = 3;
							displayLevel();
							g_eGameState = S_GAME;
							break;
						}
					case 7: 
						{
							currentLevel = 8;//Map8
							Health = 3;
							displayLevel();
							g_eGameState = S_GAME;
							break;
						}
					case 8:
						{
							currentLevel = 9;//Map9
							Health = 3;
							displayLevel();
							g_eGameState = S_GAME;
							break;
						}
					case 9:
						{
							currentLevel = 10;//Map10
							Health = 3;
							displayLevel();
							g_eGameState = S_GAME;
							break;
						}
					case 10: g_eGameState = S_MAINMENU; break;
				}
			}

	else if (g_abKeyPressed[K_BACK])
	{
		bSomethingHappened = true;
		g_eGameState = S_MAINMENU;              //Only one that jumps 2... WHYYYYYYYY???
	}
	else if (GetAsyncKeyState(VK_ESCAPE) != 0)
	{
		g_bQuitGame = true;
	}
	if (bSomethingHappened)
			 {
				// set the bounce time to some time in the future to prevent accidental triggers
				g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
			 }
}
void updateOptionsMenu()
{
	bool bSomethingHappened = false;
    if (g_dBounceTime > g_dElapsedTime)
        return;
	if (g_abKeyPressed[K_UP])
			{
				bSomethingHappened = true;
				OptionsPointer--;
				if (OptionsPointer == -1)
				{
					OptionsPointer = 2;
				}
			}
			else if (g_abKeyPressed[K_DOWN])
			{
				bSomethingHappened = true;
				OptionsPointer++;
				if (OptionsPointer == 3)
				{
					OptionsPointer = 0;
				}
			}
			else if (g_abKeyPressed[K_RETURN])
			{
				bSomethingHappened = true;
				switch(OptionsPointer)
				{

					case 0:
						{
							g_eGameState = S_LEVELMENU; 
						}break;
					case 1: 
						{
							g_eGameState = S_OPTIONS;
						}break;
					case 2:
						{
							g_eGameState = S_MAINMENU;
						}break;
				}
			}
			else if (GetAsyncKeyState(VK_ESCAPE) != 0)
			{
				g_bQuitGame = true;
			}
			if (bSomethingHappened)
			 {
				// set the bounce time to some time in the future to prevent accidental triggers
				g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
			 }
}
void updateInstruct()
{
	if (g_abKeyPressed[K_BACK])
	{
				g_eGameState = S_MAINMENU;
	}
}

void lifepoint(){

	COORD c;
	g_Console.writeToBuffer(64, 11, "Tries Left: " ,0x0B);
	for (int i = 0; i < Health; i++)
	{
		g_Console.writeToBuffer(64+i, 12, (char)3 ,0x04);
	}

	if (g_eGameState == S_LEVELMENU)
	{
		Health = 3;
	}
}

void loselife() {

	
		Health -= 1;
		if (Health == -1)
		{
			  g_bQuitGame = true;
		}

}
