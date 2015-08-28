// This is the main file for the game logic and function
//
//
#include "record.h"
#include "game.h"
#include "map.h"
#include "update.h"
#include "render.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

using std::string;

double  g_dElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];
bool    g_prevkey[K_COUNT];

bool something = false;

int currentLevel;           // Current Level ~.~


int Health = 3;
// Game specific variables here
SGameChar   g_sChar;
EGAMESTATES g_eGameState = S_MAINMENU;
double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once

int x = g_sChar.m_cLocation.X;
int y = g_sChar.m_cLocation.Y;
// Console object
Console g_Console(80, 25, "SP1 Framework");

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
    g_Console.setConsoleFont(0, 36, L"Arial");
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
	g_prevkey[K_UP];
	g_prevkey[K_DOWN];
	g_prevkey[K_LEFT];
	g_prevkey[K_RIGHT];
	g_prevkey[K_SPACE];
	g_prevkey[K_ESCAPE];
	g_prevkey[K_BACK];
	g_prevkey[K_RETURN];
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
		case S_CHARSELECT : updateCharSelect();
			break;
		case S_RECORD : updateHSMenu();
			break;
		case S_HIGHSCORES : updateHighscore();
			break;
		case S_KEYNAME : gettime();
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
		case S_CHARSELECT :renderCharSelect();
			break;
		case S_RECORD : renderHSMenu();
			break;
		case S_HIGHSCORES : readHS();
			break;
		case S_KEYNAME : keyname();
			break;
		case S_GAMEOVER : gameover();
			break;
    }
	    renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
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
		g_eGameState = S_KEYNAME;
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
		g_dElapsedTime = 0.0;
		bSomethingHappened = true;
		g_sChar.m_cLocation.X = 28;
		g_sChar.m_cLocation.Y = 16;
		g_eGameState = S_LEVELMENU;
		bSomethingHappened = true;
	}
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

	refreshtime();

}
void renderCharacter()
{
    // Draw the location of the character
    WORD charColor = 0x0C;
   if (g_sChar.gamechar == 0)
	{
		g_Console.writeToBuffer(g_sChar.m_cLocation, (char)1, charColor);
	} else {
		g_Console.writeToBuffer(g_sChar.m_cLocation, g_sChar.gamechar, charColor);
	}
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
    /*ss.str("");
    ss << g_dElapsedTime << "secs";
    c.X = g_Console.getConsoleSize().X - 15;
    c.Y = 9;
    g_Console.writeToBuffer(c, ss.str(), 0x59);
	*/


}
void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
}

void lifepoint(){
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
			  g_eGameState = S_GAMEOVER;
			  g_dElapsedTime = 0.0;
		}
}

void gameover() {

	std::string line;
 
    std::ifstream Reader ("gameover.txt");             //Open file
 
	if (Reader.is_open())
	{
		int y = 2;
		while (getline (Reader, line))
		{
			line;
			g_Console.writeToBuffer(15, y, line, 0x04);
			y++;
		}
		
	}
	Reader.close();

	g_Console.writeToBuffer(15,20, "         PRESS ENTER TO RETURN TO MAINMENU         ", 0x04);
	
	if (g_abKeyPressed[K_RETURN])
	{
		 g_eGameState = S_MAINMENU;
	}
}