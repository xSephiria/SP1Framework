#include "update.h"
#include "game.h"
#include "Framework\console.h"

extern double  g_dElapsedTime;
//extern double  g_dDeltaTime;
extern double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once

extern bool g_abKeyPressed[K_COUNT];
extern int currentLevel;
extern int Health;
extern void displayLevel();
extern EGAMESTATES g_eGameState;
extern SGameChar   g_sChar;

int MenuP = 0;              // "Cursors" for main menu
int &MenuPointer = MenuP;
int LevelP = 0;               // "Cursors" for level menu
int &LevelPointer = LevelP;
int OptionsP = 0;
int &OptionsPointer = OptionsP;
int CharP = 0;
int &CharPointer = CharP;

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
							g_eGameState = S_CHARSELECT; 
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
void updateCharSelect() {

	char Char[4] ={(char)255,(char)1,(char)2,(char)3,}; 
	bool bSomethingHappened = false;
    if (g_dBounceTime > g_dElapsedTime)
        return;

			if (g_abKeyPressed[K_LEFT])
					{
						bSomethingHappened = true;
						CharPointer--;
						if (CharPointer == -1)
						{
							CharPointer = 3;
						}
					}
			else if (g_abKeyPressed[K_RIGHT])
					{
						bSomethingHappened = true;
						CharPointer++;
						if (CharPointer == 4)
						{
							CharPointer = 0;
						}
					}
			else if (g_abKeyPressed[K_RETURN])
					{
						bSomethingHappened = true;
							switch (CharPointer)
							{
							case 0 : {
								g_sChar.gamechar = Char[0];
								g_eGameState = S_MAINMENU;
							} break;
							case 1 : {
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
									 

	if (bSomethingHappened)
			 {
				// set the bounce time to some time in the future to prevent accidental triggers
				g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
			 }

}
void gameplay()            // gameplay logic
{
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter();    // moves the character, collision detection, physics, etc
                        // sound can be played here too.
	
}
