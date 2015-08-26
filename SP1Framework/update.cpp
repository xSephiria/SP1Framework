#include "update.h"
#include "game.h"
#include "record.h"
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
int keyCount = 0;

/*void updateMenu()
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
}*/
void updateMenu()
{
	pointing();
}
void updateLevelMenu()
{
	bool bSomethingHappened = false;
    levelpoint();
	
	if (g_abKeyPressed[K_ESCAPE])
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
	optionpoint();
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
void updateCharSelect() {

	charpoint();

}
void gameplay()            // gameplay logic
{
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter();    // moves the character, collision detection, physics, etc
                        // sound can be played here too.
	
}
void pointing()
{
	
	if (g_abKeyPressed[K_UP] != 0)
	{
		if(keyCount == 0)
		{
		MenuPointer--;
		
		if (MenuPointer == -1)
		{
			MenuPointer = 3;
		}
		}
		keyCount = 1;
	}
	

	else if ( g_abKeyPressed[K_DOWN] != 0)

	{
		if (keyCount == 0)
		{
			MenuPointer++;
			if (MenuPointer == 4)
			{
				MenuPointer = 0;
			}
		}
		
		keyCount = 1;
	}
	

	else if ( g_abKeyPressed[K_RETURN] != 0)
	{
		if (keyCount == 0)
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
	keyCount = 1;
	}
		
		
	

	else
	{
		keyCount = 0;
	}
}

void levelpoint()
{
	if ( g_abKeyPressed[K_UP] != 0)
	{
		if(keyCount == 0)
		{
		LevelPointer -= 1;
		

		if (LevelPointer == -1)
		{
			LevelPointer = 10;
		}
		}
		keyCount = 1;
	}
	

	else if ( g_abKeyPressed[K_DOWN] != 0)

	{
		if (keyCount == 0)
		{
			LevelPointer += 1;
			if (LevelPointer == 11)
			{
				LevelPointer = 0;
			}
		}
		keyCount = 1;
	}
	
	

	else if ( g_abKeyPressed[K_RETURN] != 0)
	{
		if (keyCount == 0)
		{
				Health = 3;
				g_dElapsedTime = 0;
				switch(LevelPointer)
				{
					case 0:
						{
							currentLevel = 1;//Map1
							displayLevel();
							break;
						}
					case 1:
						{
							currentLevel = 2;//Map2
							displayLevel();
							break;
						}
					case 2:
						{
							currentLevel = 3;//Map3
							displayLevel();
							break;
						}
					case 3:
						{
							currentLevel = 4;//Map4
							displayLevel();
							break;
						}
					case 4:
						{
							currentLevel = 5;//Map5
							displayLevel();
							break;
						}
					case 5:
						{
							currentLevel = 6;//Map6
							displayLevel();
							break;
						}
					case 6:
						{
							currentLevel = 7;//Map7
							displayLevel();
							break;
						}
					case 7: 
						{
							currentLevel = 8;//Map8
							displayLevel();
							break;
						}
					case 8:
						{
							currentLevel = 9;//Map9
							displayLevel();
							break;
						}
					case 9:
						{
							currentLevel = 10;//Map10
							displayLevel();
							break;
						}
					case 10: g_eGameState = S_MAINMENU; break;
				}
				g_eGameState = S_GAME;
		}
		keyCount = 1;
	}
		
		
	

	else
	{
		keyCount = 0;
	}
}

void optionpoint()
{
	if (g_abKeyPressed[K_UP])
			{
				if (keyCount == 0)
				{
				OptionsPointer--;
				if (OptionsPointer == -1)
				{
					OptionsPointer = 2;
				}
				}
				keyCount = 1;
			}
			else if (g_abKeyPressed[K_DOWN])
			{
				if (keyCount == 0)
				{
				OptionsPointer++;
				if (OptionsPointer == 3)
				{
					OptionsPointer = 0;
				}
				}
				keyCount = 1;
			}
			else if (g_abKeyPressed[K_RETURN])
			{
				if (keyCount == 0)
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
				keyCount = 1;
			}
			else
	{
		keyCount = 0;
	}
}

void charpoint()
{
	char Char[4] ={(char)255,(char)1,(char)2,(char)3,}; 
	if (g_abKeyPressed[K_LEFT])
					{
						if (keyCount == 0)
						{
						
						CharPointer--;
						if (CharPointer == -1)
						{
							CharPointer = 3;
						}
						}
						keyCount = 1;
					}
			else if (g_abKeyPressed[K_RIGHT])
					{
						if (keyCount == 0)
						{
						
						CharPointer++;
						if (CharPointer == 4)
						{
							CharPointer = 0;
						}
						}
						keyCount = 1;
					}
			else if (g_abKeyPressed[K_RETURN])
					{
						if (keyCount == 0)
						{
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
						keyCount = 1;

			}
			else 
			{
				keyCount = 0;
			}
}
