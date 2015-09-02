#include "update.h"
#include "game.h"
#include "record.h"
#include "Framework\console.h"

extern double  g_dElapsedTime;
extern double  g_dDeltaTime;
extern double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once

extern bool g_abKeyPressed[K_COUNT];
extern bool g_abOnKeyPress[K_COUNT];
extern int currentLevel;
extern int Health;
extern void displayLevel();
extern EGAMESTATES g_eGameState;
extern SGameChar   g_sChar;
extern Console g_Console;
extern string PlayerName;
extern void openMap(int i);
extern bool something;
int MenuP = 0;              // "Cursors" for main menu
int &MenuPointer = MenuP;
int LevelP = 0;               // "Cursors" for level menu
int &LevelPointer = LevelP;
int OptionsP = 0;
int &OptionsPointer = OptionsP;  // "Cursors" for Options menu
int CharP = 0;
int &CharPointer = CharP;
int HSP = 0;                   // "Cursors" for Highscore menu
int &HSPointer = HSP;
int NP = 0;
int &NamePointer = NP;


void updateMenu()
{
	if (g_abOnKeyPress[K_UP])
		{
			MenuPointer--;
			if (MenuPointer == -1) 
				{
					MenuPointer = 3;
				}
		}
	else if (g_abOnKeyPress[K_DOWN])
		{
			MenuPointer++;
			if (MenuPointer == 4)
			{
				MenuPointer = 0;
			}
		}
	else if (g_abOnKeyPress[K_RETURN])
		{
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
}
void updateLevelMenu()
{
	bool bSomethingHappened = false;
	if (g_abOnKeyPress[K_UP])
		{
			LevelPointer -= 1;
			if (LevelPointer == -1)
				{
					LevelPointer = 10;
				}
		}
	else if (g_abOnKeyPress[K_DOWN])
		{
			LevelPointer += 1;
			if (LevelPointer == 11)
				{
					LevelPointer = 0;
				}
		}
	else if (g_abOnKeyPress[K_RETURN])
		{  
			if (LevelPointer == 10)
			{
				g_eGameState = S_MAINMENU;
			}
			else
			{
				openMap(LevelPointer);
				Health = 3;
				g_dElapsedTime = 0.0;
				g_eGameState = S_GAME;
			}
	if (g_abKeyPressed[K_ESCAPE])
	{
		g_bQuitGame = true;
	}
	if (bSomethingHappened= true)
		{
			// set the bounce time to some time in the future to prevent accidental triggers
			g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
		}
	}
}
void updateOptionsMenu()
{
	if (g_abOnKeyPress[K_UP])
	{
		OptionsPointer--;
		if (OptionsPointer == -1)
		{
			OptionsPointer = 2;
		}
	}
	else if (g_abOnKeyPress[K_DOWN])
	{
		OptionsPointer++;
		if (OptionsPointer == 3)
		{
			OptionsPointer = 0;
		}
	}
	else if (g_abOnKeyPress[K_RETURN])
	{
		switch(OptionsPointer)
		{
			case 0:
				{
					g_eGameState = S_CHARSELECT;
				}break;
			case 1:
				{
					g_eGameState = S_RECORD;
				}break;
			case 2:
				{
					g_eGameState = S_MAINMENU;
				}break;
		}
	}
	if (g_abKeyPressed[K_ESCAPE] != 0)
	{
		g_bQuitGame = true;
	}
}
void updateInstruct()
{
	if (g_abKeyPressed[K_BACK])
	{
		g_eGameState = S_MAINMENU;
	}
	else if (g_abKeyPressed[K_ESCAPE])
	{
		g_bQuitGame = true;
	}
}
void updateCharSelect() 
{
	char Char[4] ={(char)255,(char)1,(char)2,(char)3,};
		if (g_abOnKeyPress[K_LEFT])
			{
				CharPointer--;
				if (CharPointer == -1)
				{
				CharPointer = 3;
				}
			}
		else if (g_abOnKeyPress[K_RIGHT])
			{
				CharPointer++;
				if (CharPointer == 4)
				{
				CharPointer = 0;
				}
			}
		else if (g_abOnKeyPress[K_RETURN])
			{
				switch (CharPointer)
				{
				case 0 :{
					g_sChar.gamechar = Char[0];
					g_eGameState = S_MAINMENU;
						} break;
				case 1: {
					g_sChar.gamechar = Char[1];
					g_eGameState = S_MAINMENU;
						} break;
				case 2 : {
					g_sChar.gamechar = Char[2];
					g_eGameState = S_MAINMENU;
						} break;
				case 3 : {
					g_sChar.gamechar = Char[3];
					g_eGameState = S_MAINMENU;
						} break;
				default: {
					g_sChar.gamechar = (char)1;
						} break;
				}
			}
}
void gameplay()            // gameplay logic
{
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter();    // moves the character, collision detection, physics, etc
                        // sound can be played here too.
}

void updateHSMenu()
{
	if ( g_abOnKeyPress[K_UP])
		{
			HSPointer -= 1;
			if (HSPointer == -1)
			{
				HSPointer = 10;
			}
		}
	else if (g_abOnKeyPress[K_DOWN])
		{
			HSPointer += 1;
			if (HSPointer == 11)
			{
				HSPointer = 0;
			}
		}
	else if ( g_abOnKeyPress[K_RETURN])
		{
			if (HSPointer == 10)
			{
				g_eGameState = S_MAINMENU;
			}
			else
			{
				readHS(HSPointer);
				g_eGameState = S_HIGHSCORES;
			}
		}
}
void updateHighscore()
{
	if (g_abKeyPressed[K_BACK])
	{
		g_eGameState = S_RECORD;
	}
}
