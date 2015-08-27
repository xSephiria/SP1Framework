#include "update.h"
#include "game.h"
#include "record.h"
#include "Framework\console.h"

extern double  g_dElapsedTime;
//extern double  g_dDeltaTime;
extern double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once

extern bool g_abKeyPressed[K_COUNT];
extern bool g_prevkey[K_COUNT];
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
int &OptionsPointer = OptionsP;  // "Cursors" for Options menu
int CharP = 0;
int &CharPointer = CharP;
int HSP = 0;                   // "Cursors" for Highscore menu
int &HSPointer = HSP;

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
	
	if (g_abKeyPressed[K_UP])
	{
		if(g_prevkey[K_UP] != g_abKeyPressed[K_UP])
		{
		MenuPointer--;
		
		if (MenuPointer == -1)
		{
			MenuPointer = 3;
		}
		}
		g_prevkey[K_UP] = g_abKeyPressed[K_UP];
	}
	

	else if ( g_abKeyPressed[K_DOWN])

	{
		if (g_prevkey[K_DOWN] != g_abKeyPressed[K_DOWN])
		{
			MenuPointer++;
			if (MenuPointer == 4)
			{
				MenuPointer = 0;
			}
		}
		
		g_prevkey[K_DOWN] = g_abKeyPressed[K_DOWN];
	}
	

	else if ( g_abKeyPressed[K_RETURN])
	{
		if (g_prevkey[K_RETURN] != g_abKeyPressed[K_RETURN])
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
	g_prevkey[K_RETURN] = g_abKeyPressed[K_RETURN];
	}
		

	else
	{
	     g_prevkey[K_UP] = g_prevkey[K_COUNT];
		 g_prevkey[K_DOWN] = g_prevkey[K_COUNT];
		 g_prevkey[K_RETURN] = g_prevkey[K_COUNT];
	}
}

void levelpoint()
{
	if ( g_abKeyPressed[K_UP])
	{
		if(g_prevkey[K_UP] != g_abKeyPressed[K_UP])
		{
		LevelPointer -= 1;
		

		if (LevelPointer == -1)
		{
			LevelPointer = 10;
		}
		}
		g_prevkey[K_UP] = g_abKeyPressed[K_UP];
	}
	

	else if (g_abKeyPressed[K_DOWN])

	{
		if (g_prevkey[K_DOWN] != g_abKeyPressed[K_DOWN])
		{
			LevelPointer += 1;
			if (LevelPointer == 11)
			{
				LevelPointer = 0;
			}
		}
		g_prevkey[K_DOWN] = g_abKeyPressed[K_DOWN];
	}
	else if ( g_abKeyPressed[K_RETURN])
	{
		if (g_prevkey[K_RETURN] != g_abKeyPressed[K_RETURN])
		{
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
		g_prevkey[K_RETURN] = g_abKeyPressed[K_RETURN];
	}
	else
	{
		 g_prevkey[K_UP] = g_prevkey[K_COUNT];
		 g_prevkey[K_DOWN] = g_prevkey[K_COUNT];
		 g_prevkey[K_RETURN] = g_prevkey[K_COUNT];
		
	}
}

void optionpoint()
{
	if (g_abKeyPressed[K_UP])
			{
				if (g_prevkey[K_UP] != g_abKeyPressed[K_UP])
				{
				OptionsPointer--;
				if (OptionsPointer == -1)
				{
					OptionsPointer = 2;
				}
				}
				g_prevkey[K_UP] = g_abKeyPressed[K_UP];
			}
			else if (g_abKeyPressed[K_DOWN])
			{
				if (g_prevkey[K_DOWN] != g_abKeyPressed[K_DOWN])
				{
				OptionsPointer++;
				if (OptionsPointer == 3)
				{
					OptionsPointer = 0;
				}
				}
				g_prevkey[K_DOWN] = g_abKeyPressed[K_DOWN];
			}
			else if (g_abKeyPressed[K_RETURN])
			{
				if (g_prevkey[K_RETURN] != g_abKeyPressed[K_RETURN])
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
				g_prevkey[K_RETURN] = g_abKeyPressed[K_RETURN];
			}
			else
	{
		 g_prevkey[K_UP] = g_prevkey[K_COUNT];
		 g_prevkey[K_DOWN] = g_prevkey[K_COUNT];
		 g_prevkey[K_RETURN] = g_prevkey[K_COUNT];
	}
}

void charpoint()
{
	char Char[4] ={(char)255,(char)1,(char)2,(char)3,}; 
	if (g_abKeyPressed[K_LEFT])
					{
						if (g_prevkey[K_LEFT] != g_abKeyPressed[K_LEFT])
						{
						
						CharPointer--;
						if (CharPointer == -1)
						{
							CharPointer = 3;
						}
						}
						g_prevkey[K_LEFT] = g_abKeyPressed[K_LEFT];
					}
			else if (g_abKeyPressed[K_RIGHT])
					{
						if (g_prevkey[K_RIGHT] != g_abKeyPressed[K_RIGHT])
						{
						
						CharPointer++;
						if (CharPointer == 4)
						{
							CharPointer = 0;
						}
						}
						g_prevkey[K_RIGHT] = g_abKeyPressed[K_RIGHT];
					}
			else if (g_abKeyPressed[K_RETURN])
					{
						if (g_prevkey[K_RETURN] != g_abKeyPressed[K_RETURN])
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
						g_prevkey[K_RETURN] = g_abKeyPressed[K_RETURN];

			}
			else 
			{
				 g_prevkey[K_LEFT] = g_prevkey[K_COUNT];
				 g_prevkey[K_RIGHT] = g_prevkey[K_COUNT];
				 g_prevkey[K_RETURN] = g_prevkey[K_COUNT];
			}
}
void updateHSMenu()
{
	if ( g_abKeyPressed[K_UP])
	{
		if(g_prevkey[K_UP] != g_abKeyPressed[K_UP])
		{
			HSPointer -= 1;
			if (HSPointer == -1)
			{
				HSPointer = 10;
			}
			}
			g_prevkey[K_UP] = g_abKeyPressed[K_UP];
	}
	else if (g_abKeyPressed[K_DOWN])
	{
		if (g_prevkey[K_DOWN] != g_abKeyPressed[K_DOWN])
		{
			HSPointer += 1;
			if (HSPointer == 11)
			{
				HSPointer = 0;
			}
		}
		g_prevkey[K_DOWN] = g_abKeyPressed[K_DOWN];
	}
	else if ( g_abKeyPressed[K_RETURN])
	{
		if (g_prevkey[K_RETURN] != g_abKeyPressed[K_RETURN])
		{
				switch(HSPointer)
				{
					case 0:
						{
							currentLevel = 1;
							g_eGameState = S_HIGHSCORES;
							break;
						}
					case 1:
						{
							currentLevel = 2;
							g_eGameState = S_HIGHSCORES;
							break;
						}
					case 2:
						{
							currentLevel = 3;//Map3
							g_eGameState = S_HIGHSCORES;
							break;
						}
					case 3:
						{
							currentLevel = 4;//Map4
							g_eGameState = S_HIGHSCORES;
							break;
						}
					case 4:
						{
							currentLevel = 5;//Map5
							g_eGameState = S_HIGHSCORES;
							break;
						}
					case 5:
						{
							currentLevel = 6;//Map6
							g_eGameState = S_HIGHSCORES;
							break;
						}
					case 6:
						{
							currentLevel = 7;//Map7
							g_eGameState = S_HIGHSCORES;
							break;
						}
					case 7: 
						{
							currentLevel = 8;//Map8
							g_eGameState = S_HIGHSCORES;
							break;
						}
					case 8:
						{
							currentLevel = 9;//Map9
							g_eGameState = S_HIGHSCORES;
							break;
						}
					case 9:
						{
							currentLevel = 10;//Map10
							g_eGameState = S_HIGHSCORES;
							break;
						}
					case 10: g_eGameState = S_OPTIONS; break;
				}
				g_prevkey[K_RETURN] = g_abKeyPressed[K_RETURN];
		}
	}
		else 
			{
				 g_prevkey[K_UP] = g_prevkey[K_COUNT];
				 g_prevkey[K_DOWN] = g_prevkey[K_COUNT];
				 g_prevkey[K_RETURN] = g_prevkey[K_COUNT];
			}
}
void updateHighscore()
{
	if (g_abKeyPressed[K_BACK])
	{
				g_eGameState = S_RECORD;
	}
}