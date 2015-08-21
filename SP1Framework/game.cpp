// This is the main file for the game logic and function
//
//
#include "game.h"
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
char map[25][60] = {0};



int currentLevel;           // Current Level ~.~

int MenuP = 0;              // "Cursors" for main menu
int &MenuPointer = MenuP;
int LevelP = 0;               // "Cursors" for level menu
int &LevelPointer = LevelP;

// Game specific variables here
SGameChar   g_sChar;
EGAMESTATES g_eGameState = S_SPLASHSCREEN;
double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once

int x = g_sChar.m_cLocation.X;
int y = g_sChar.m_cLocation.Y;
// Console object
Console g_Console(79, 28, "SP1 Framework");

void map1()
{
	char Nmap[25][60] = {
	"###########################################################",
	"#                                                         #",
	"#                                                         #",
	"#                      STAGE ONE                          #",
	"#                                                         #",
	"#                                                         #",
	"#                          ###                            #",
	"#                          #@#                            #",
	"#                         ## ##                           #",
	"#                         #   #                           #",
	"#                         #BBB#                           #",
	"#                         #   #                           #",
	"#                         #   #                           #",
	"#                         #BBB#                           #",
	"#                         #   #                           #",
	"#                         ## ##                           #",
	"#                          #S#                            #",
	"#                          ###                            #",
	"#                                                         #",
	"#                                                         #",
	"#                                                         #",
	"#                       EASY PEASY                        #",
	"#                                                         #",
	"#                                                         #",
	"###########################################################",
	};
	for (int cols = 0; cols < 25; cols++)
	{
		for (int rows = 0; rows < 60; rows++)
		{
			if (Nmap[cols][rows] == G_WALL)
			{
				Nmap[cols][rows] = (char)178;
			}
			if (Nmap[cols][rows] == G_BOX)
			{
				Nmap[cols][rows] = (char)254;
			}
			map[cols][rows] = Nmap[cols][rows];
		}
	}
	
}
void map2()
{
	char Nmap[25][60] = {
	"###########################################################",
	"#                                                         #",
	"#                                                         #",
	"#                       STAGE TWO                         #",
	"#                                                         #",
	"#                                                         #",
	"#                          ###                            #",
	"#                        ###@###                          #",
	"#                        #B B B#                          #",
	"#                        #   B #                          #",
	"#                        #B # B#                          #",
	"#                        # B B #                          #",
	"#                        #B B B#                          #",
	"#                        #  #  #                          #",
	"#                        # B B #                          #",
	"#                        ### ###                          #",
	"#                         # S #                           #",
	"#                         #####                           #",
	"#                                                         #",
	"#                                                         #",
	"#                      Still OK Lah                       #",
	"#                                                         #",
	"#                                                         #",
	"#                                                         #",
	"###########################################################",
	};


	for (int cols = 0; cols < 25; cols++)
	{
		for (int rows = 0; rows < 60; rows++)
		{
			if (Nmap[cols][rows] == G_WALL)
			{
				Nmap[cols][rows] = (char)178;
			}
			if (Nmap[cols][rows] == G_BOX)
			{
				Nmap[cols][rows] = (char)254;
			}
			map[cols][rows] = Nmap[cols][rows];
		}
	}
}
void map3() {

	char Nmap[25][60] = {
	"###########################################################",
	"#                         ##@##                           #",
	"#                        ##   ##                          #",
	"#                        #BB BB#                          #",
	"#                        # BBB #                          #",
	"#                        #B   B#                          #",
	"#                        # BBB #                          #",
	"#                        #     #                          #",
	"#                       ##B##  ##                         #",
	"#                       #B  ##  #                         #",
	"#                       # B B B ##                        #",
	"#      STAGE THREE      #B # B   #       Having Fun?      #",
	"#                       #   B B ##                        #",
	"#                       ##  ##  #                         #",
	"#                       ## B ####                         #",
	"#                         #   #                           #",
	"#                         # S #                           #",
	"#                         #####                           #",
	"#                                                         #",
	"#                                                         #",
	"#                                                         #",
	"#                                                         #",
	"#                                                         #",
	"#                                                         #",
	"###########################################################",
	};

	for (int cols = 0; cols < 25; cols++)
	{
		for (int rows = 0; rows < 60; rows++)
		{
			if (Nmap[cols][rows] == G_WALL)
			{
				Nmap[cols][rows] = (char)178;
			}
			if (Nmap[cols][rows] == G_BOX)
			{
				Nmap[cols][rows] = (char)254;
			}
			map[cols][rows] = Nmap[cols][rows];
		}
	}
}
void map4()
{

	char Nmap[25][60] = {
	"###########################################################",
	"#                                                         #",
	"#                                                         #",
	"#                                                         #",
	"#              ##########################                 #",
	"#              #                    B   #                 #",
	"#              #   ##################   #                 #",
	"#              # BB@B#   STAGE4     #   #                 #",
	"#              #  B  #              #   #                 #",
	"#              #######         ######   #                 #",
	"#              #######        ##        #                 #",
	"#                            ## B #######                 #",
	"#                           ## B ##                       #",
	"#                         ### B ##                        #",
	"#                         ## B ##                         #",
	"#                         #   ##                          #",
	"#                         # S #                           #",
	"#                         #####                           #",
	"#                                                         #",
	"#                                                         #",
	"#                         WUT???                          #",
	"#                                                         #",
	"#                                                         #",
	"#                                                         #",
	"###########################################################",
	};

	for (int cols = 0; cols < 25; cols++)
	{
		for (int rows = 0; rows < 60; rows++)
		{
			if (Nmap[cols][rows] == G_WALL)
			{
				Nmap[cols][rows] = (char)178;
			}
			if (Nmap[cols][rows] == G_BOX)
			{
				Nmap[cols][rows] = (char)254;
			}
			map[cols][rows] = Nmap[cols][rows];
		}
	}
}
void map5() {

	char Nmap[25][60] = {
	"###########################################################",
	"#                                                         #",
	"#                                                         #",
	"#                                                         #",
	"#                                      Stage 5            #",
	"#                                                         #",
	"#                                                         #",
	"#                                                         #",
	"#           still easy?                                   #",
	"#                                                         #",
	"#                                                         #",
	"#                                                         #",
	"#                            ####                         #",
	"#                        #####  #####                     #",
	"#                      ###    B     #                     #",
	"#                      #  B### #BBB #                     #",
	"#                      # # #S# #B B #                     #",
	"#                     ## ### ###B   #                     #",
	"###########           # B # B ##B BB#                     #",
	"# B    #B##          ##B B#    #BBB #                     #",
	"# B#B@B#BB#          # B  #  B #B   #                     #",
	"#  #B#B BB#  ####### ## B ### ##BBBB#                     #",
	"#       B #### B   #####  # # ##### ##                    #",
	"##BB#BBB#         B      #  #   B    #                    #",
	"###########################################################",
	};
	for (int cols = 0; cols < 25; cols++)
	{
		for (int rows = 0; rows < 60; rows++)
		{
			if (Nmap[cols][rows] == G_WALL)
			{
				Nmap[cols][rows] = (char)178;
			}
			if (Nmap[cols][rows] == G_BOX)
			{
				Nmap[cols][rows] = (char)254;
			}
			map[cols][rows] = Nmap[cols][rows];
		}
	}

}
void map6() {

	char Nmap[25][60] = {
	"###########################################################",
	"#                                                         #",
	"#                                                         #",
	"#                                                         #",
	"#                          ###                            #",
	"#                         ## ##################           #",
	"#                         # B B               #           #",
	"#                         #B ############### ##           #",
	"#                      #### ##       #   B #B#            #",
	"#                      # # B #       # B   B #            #",
	"#                      # B ###       #B B  # #            #",
	"#     Stage 6          # B  #        ## ######            #",
	"#   Are you ready?    ##B######       # #########         #",
	"#                     #   #           #  BB  B  #         #",
	"#                     #BBB#           # B    B  #         #",
	"#                     #   #######     ####### B #         #",
	"#                     ## ###SB  #           ##@##         #",
	"#                     #     BB###            ###          #",
	"#                     ####### #                           #",
	"#                           ###                           #",
	"#                                                         #",
	"#                                                         #",
	"#                                                         #",
	"#                                                         #",
	"###########################################################",
	};

	for (int cols = 0; cols < 25; cols++)
	{
		for (int rows = 0; rows < 60; rows++)
		{
			if (Nmap[cols][rows] == G_WALL)
			{
				Nmap[cols][rows] = (char)178;
			}
			if (Nmap[cols][rows] == G_BOX)
			{
				Nmap[cols][rows] = (char)254;
			}
			map[cols][rows] = Nmap[cols][rows];
		}
	}
}
void map7() 
{

	char Nmap[25][60] = {
	"###########################################################",
	"#                                                         #",
	"#                                                         #",
	"#                                                         #",
	"#                                                         #",
	"#         #############################  ###              #",
	"#         #    B    B   B  B    B   B #  # ###            #",
	"#         #@BB   BB  B B   B B    B # ####B B###          #",
	"#         #######  BB B B  B ######## ## B B B ##         #",
	"#               ##############     #      B B B ##        #",
	"#               #B     B   B ##    ##### B B B   #        #",
	"#               #  BB  B  ##  ##   ############# #        #",
	"#               # B#######  B  #              ## ##       #",
	"#               #B #     ##B#B #  Stage 7    ##   ##      #",
	"#               #  #     ## B  #   SO CLOSE  #BB BB#      #",
	"#               #BB#      # ####             # BBB #      #",
	"#               #  #      # S#       ####### #B   B#      #",
	"#               #  #      #######    #   B # # BBB #      #",
	"#               #BB############ ###  # #B ## #     #      #",
	"#               #    ## B B  B  B #### ## #  ### ###      #",
	"#               # ##    B B  B  B     B # ####BB ##       #",
	"#               ####### B B  B  B ####### B       #       #",
	"#                     #############     ###########       #",
	"#                                                         #",
	"###########################################################",
	};
	for (int cols = 0; cols < 25; cols++)
	{
		for (int rows = 0; rows < 60; rows++)
		{
			if (Nmap[cols][rows] == G_WALL)
			{
				Nmap[cols][rows] = (char)178;
			}
			if (Nmap[cols][rows] == G_BOX)
			{
				Nmap[cols][rows] = (char)254;
			}
			map[cols][rows] = Nmap[cols][rows];
		}
	}

}
void map8() {

	char Nmap[25][60] = {
	"###########################################################",
	"#                                                         #",
	"#  Stage 8                                                #",
	"#              ##################################         #",
	"#             ##   #  B  # B   B#  B B B # B # B####      #",
	"#            ## B  #  #  # BB BB# B B # B B B # # B##     #",
	"#           ## B B B  #  B  B B ## B B # # B B     B##    #",
	"#           # B #  #########BB B# B # B B ## ## B B # ##  #",
	"#          ##  #  #####UMAD?#BBB#B # B B###bRO?### B B #  #",
	"#         ## B## ##########  #  # B B #############  ##   #",
	"#      ####BB #  B   #B B  # B B### #####         B B ##  #",
	"#    ###  B B ####B###  #       #  B  #   B ##########    #",
	"#    #   B  B  #######  B ########## ####  #B B      #    #",
	"#    # ####B##########  ### B   ### B #  BB B   ###B #    #",
	"#    #     B##  B  ####    B #  B     #     B B####  #    #",
	"#    ### B   ##B  B   #############################B #    #",
	"#      ## BB  ##B  B  B     S#@                ####  #    #",
	"#       ##  BB # B  ######################### BB### B##   #",
	"#        ##   B ### B            ##          B ##   B #   #",
	"#         ###  B  ############# ### ##############BBBB#   #",
	"#           ###    B     BB   B ##   B    B    B      #   #",
	"#             #####   BB     B  ###BB BB  B B   B #####   #",
	"#                  ################################       #",
	"#                                                         #",
	"###########################################################",
	};

	for (int cols = 0; cols < 25; cols++)
	{
		for (int rows = 0; rows < 60; rows++)
		{
			if (Nmap[cols][rows] == G_WALL)
			{
				Nmap[cols][rows] = (char)178;
			}
			if (Nmap[cols][rows] == G_BOX)
			{
				Nmap[cols][rows] = (char)254;
			}
			map[cols][rows] = Nmap[cols][rows];
		}
	}
}
void map9() {

	char Nmap[25][60] = {
        "###########################################################",
        "#       B     BBB         #                    B   BB  B  #",
        "#         #        ######          #######     BB   B     #",
        "##B B#BBB###########REKT############FACES##############   #",
        "#         #       B######B         B######B           #   #",
        "##BBB# BB##      B        B       B        B    #B  # #   #",
        "# B       #     B  B   B   B     B  B    B  B   B#B#  #BBB#",
        "##BBB#B B##     B          B     B          B    B#   #   #",
        "#         #     B   BBBB   B     B  B    B  B   B#B#  #   #",
        "##BBB# B###      B B    B B       B  BBBB  B        # # B #",
        "#     B   #       BBBBBBBB         BBBBBBBB  BBBB######B B#",
        "#    #    ## ##############################BBBB    BB##  B#",
        "#   B     #                               #BBBBB B BB #   #",
        "#  B      ########################B#B B B##BBBBBB B   #   #",
        "##BBB#BB###                       B B## B######### B  #   #",
        "#         #     ###############BBBB #  BB##     #BB BB#   #",
        "########  #     ########### S # B # BBB B## LOL #   B #   #",
        "#         #BB BB# LEVEL  ##   #   B    B ##     #   # #B B#",
        "# B######## B B #  NINE  ##   # BBBB  BB ##########BB #BB #",
        "#     B BB#B B B# LET'S  ## B #  B BB  BB### BB   #   #B B#",
        "######  BB# BBB #  GO    ##  B#   BB B B ##B  B       # B #",
        "#   B     # BB  ###########B B# ########### BBB####BBB#   #",
        "# #########  B  #         ##  ###  B    BB    ##  #B B#BB #",
        "#            B  #         #B        BB    B  B#   #B  # @ #",
        "###########################################################",
        };
	for (int cols = 0; cols < 25; cols++)
	{
		for (int rows = 0; rows < 60; rows++)
		{
			if (Nmap[cols][rows] == G_WALL)
			{
				Nmap[cols][rows] = (char)178;
			}
			if (Nmap[cols][rows] == G_BOX)
			{
				Nmap[cols][rows] = (char)254;
			}
			map[cols][rows] = Nmap[cols][rows];
		}
	}
}
void map10() {

	char Nmap[25][60] = {
	"###########################################################",
	"#         #          #         B      #   B               #",
	"#               #  # # #######B # BBB ##B# ###########    #",
	"#  ##############  # # #     #  #B   B#   B#         ##BB##",
	"#  #    LAST    #  # # # ### #BB# BBB #  B## ####### #    #",
	"#  #    STAGE   #B # #   ##  #  #BB BB# B  # #     # #    #",
	"#  ##############B # #  ### ##BB##   ###B# # # ### # #BB#B#",
	"#       # B        # #BBB##  #  ### ###    # # #@# # #    #",
	"#   ##  # ########## #   ### #BB#     #  B## #   # # #    #",
	"#BBB##    #  B       BB  ##B    #B###B# B  # ##### # #BBB##",
	"#  B   BB # B# # # #B BB  ####### ### # ####       # #    #",
	"#  ##B## B#   ##B B  B##  ####### BB B# B ########## #    #",
	"# B##  #B## BB # # B# #  ########   B # # #          #B#BB#",
	"#B   B    #       B#  #  #  # B #  BB #    B #########    #",
	"## B ############    ##  #      ##B  B######## # # # B  #B#",
	"##B B#JUST DO IT# ##     # BB#  #BB BB#     ##B # B B ##  #",
	"## B #######################S#BB#  B B#  # B ##B B #   B B#",
	"#  ###B   B  B   B  BB     ###  #  B B#B ## B ##B   B # B #",
	"# ##B    BB   B BB B     B B#  B#B BB # B### B ######### ##",
	"# ##BBB################## B #   #B B B#  B ## B #    B    #",
	"#  #B  B         B    B #B  #   #BB BB### B ##B # #########",
	"## #B B########    BBB B# B #BBB#BB B B ## B # B#         #",
	"## ##### B B  ####### B #B B#   ### B B  ##  #  ######### #",
	"#B                 B    ##  B   ###  BB     ##            #",
	"###########################################################",
	};

	for (int cols = 0; cols < 25; cols++)
	{
		for (int rows = 0; rows < 60; rows++)
		{
			if (Nmap[cols][rows] == G_WALL)
			{
				Nmap[cols][rows] = (char)178;
			}
			if (Nmap[cols][rows] == G_BOX)
			{
				Nmap[cols][rows] = (char)254;
			}
			map[cols][rows] = Nmap[cols][rows];
		}
	}
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
    // Set precision for floating point output
    g_dElapsedTime = 0.0;
    g_dBounceTime = 0.0;

    // sets the initial state for the game
    g_eGameState = S_SPLASHSCREEN;

    g_sChar.m_cLocation.X = 28;
    g_sChar.m_cLocation.Y = 16;
    g_sChar.m_bActive = true;
    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 36, L"Consolas");
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
        case S_SPLASHSCREEN : renderSplashScreen(); // game logic for the splash screen
            break;
        case S_GAME: gameplay();  // gameplay logic when we are in the game
            break;
		case S_LEVELMENU : levelMenu(); //Level Menu
			break;
		//case S_OPTIONS : optionsMenu();
			//break;
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
        case S_SPLASHSCREEN: renderSplashScreen();
            break;
        case S_GAME: renderGame();
            break;
		case S_LEVELMENU : renderLevelMenu(); 
			break;
    }
	
    renderFramerate();  // renders debug information, frame rate, elapsed time, etc
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
			if( map[y - 1][x] != (char)254) //if box not present
			{ 
                g_sChar.m_cLocation.Y--;
				
			} 
			else if ( map[y - 1][x] == (char)254 && map[y-2][x] != (char)178 && map[y-2][x] != (char)254)
			{
				map[y - 2][x] = (char)254;
				g_sChar.m_cLocation.Y--;
				map[y - 1][x] = ' ';
				
			}
			else if (map[y-1][x] != (char)254 && map[y-2][x] != (char)254 )
			{
				g_sChar.m_cLocation.Y--;
			}
		}
        bSomethingHappened = true;
    }
    if (g_abKeyPressed[K_LEFT] && g_sChar.m_cLocation.X > 0)
    {
        if (map[y][x-1] != (char)178)
	    {
			if( map[y][x-1] != (char)254) //if box(ascii char 66) not present
			{ 
                g_sChar.m_cLocation.X--;	
			} 
			else if ( map[y][x-1] == (char)254 && map[y][x-2] != (char)178 && map[y][x-2] != (char)254)
			{
				map[y][x-2] = (char)254;
				g_sChar.m_cLocation.X--;
				map[y][x-1] = ' ';	
			}
			else if (map[y][x-1] != (char)254 && map[y][x-2] != (char)254 )
			{
				g_sChar.m_cLocation.X--;
			}
		}
        bSomethingHappened = true;
    }
    if (g_abKeyPressed[K_DOWN] && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
    {
       if (map[y+1][x] != (char)178)
	   {
			if( map[y + 1][x] != (char)254) //if box(ascii char 66) not present
			{ 
                g_sChar.m_cLocation.Y++;
			} 
			else if ( map[y+1][x] == (char)254 && map[y+2][x] != (char)178 && map[y+2][x] != (char)254)
			{
				map[y+2][x] = (char)254;
				g_sChar.m_cLocation.Y++;
				map[y+1][x] = ' ';
			
			}
			else if (map[y+1][x] != (char)254 && map[y+2][x] != (char)254 )
			{
				g_sChar.m_cLocation.Y++;
			}
		}
        bSomethingHappened = true;
    }
    if (g_abKeyPressed[K_RIGHT] && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
    {
       if (map[y][x+1] != (char)178)
	    {
			if( map[y][x+1] != (char)254) //if box(ascii char 66) not present
			{ 
                g_sChar.m_cLocation.X++;
			} 
			else if ( map[y][x+1] == (char)254 && map[y][x+2] != (char)178 && map[y][x+2] != (char)254)
			{
				map[y][x+2] = (char)254;
				g_sChar.m_cLocation.X++;
				map[y][x+1] = ' ';
			}
			else if (map[y][x+1] != (char)254 && map[y][x+2] != (char)254 )
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
    // quits the game if player hits the escape key
    if (g_abKeyPressed[K_ESCAPE])
        g_bQuitGame = true; 
	if (g_abKeyPressed[K_SPACE])
    {
        g_sChar.m_cLocation.X = 28;
		g_sChar.m_cLocation.Y = 16;
		displayLevel();
    }
}

void clearScreen()
{
    // Clears the buffer with this colour attribute
    g_Console.clearBuffer(0x0F);
}

void renderSplashScreen()  // renders the splash screen
{
	displayMenu();	
}
void renderLevelMenu()
{
	levelMenu();
}

void renderGame()
{
    renderMap();        // renders the map to the buffer first
    renderCharacter();  // renders the character into the buffer
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
		g_Console.writeToBuffer(j,i,map[i][j],0x0B);
		}
	}

}

void renderCharacter()
{
    // Draw the location of the character
    WORD charColor = 0x0C;
    if (g_sChar.m_bActive)
    {
        charColor = 0x0A;
    }
    g_Console.writeToBuffer(g_sChar.m_cLocation, (char)1, charColor);
}
void renderFramerate()
{
    COORD c;
    // displays the framerate
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(3);
    ss << 1.0 / g_dDeltaTime << "fps";
    c.X = g_Console.getConsoleSize().X - 9;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str());

    // displays the elapsed time
    ss.str("");
    ss << g_dElapsedTime << "secs";
    c.X = 0;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str(), 0x59);
}
void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
}
void displayMenu()
{
	string Menu[3] ={"                                   Start Game", "                                    Options", "                                      Exit"};
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
  g_Console.writeToBuffer(0,i,box[i]);
  }
	for (int i = 0; i < 3; ++i)
		{
			if (i == MenuPointer)
			{	
				 g_Console.writeToBuffer(0,10+i,Menu[i],0x0B);
			}
			else
			{
				 g_Console.writeToBuffer(0,10+i,Menu[i],0x0F);
			}
		}

			if (GetAsyncKeyState(VK_UP) != 0)
			{
				MenuPointer--;
				if (MenuPointer == -1)
				{
					MenuPointer = 2;
				}
			}
			else if (g_abKeyPressed[K_DOWN])
			{
				MenuPointer++;
				if (MenuPointer == 3)
				{
					MenuPointer = 0;
				}
			}
			else if (GetAsyncKeyState(VK_RETURN) != 0)
			{
				switch(MenuPointer)
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
							g_bQuitGame = true;
						}break;
				}
			}
			Sleep(150);
}
void levelMenu()
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

	g_Console.writeToBuffer(0,2,"                               Choose Your Level",0x0F);

	for (int i = 0; i < 11; ++i)
		{
			if (i == LevelPointer)
			{
				g_Console.writeToBuffer(0, 6+i,Menu[i],0x0B);
			}
			else
			{
				g_Console.writeToBuffer(0, 6+i,Menu[i],0x0F);
			}
		}

	if (GetAsyncKeyState(VK_UP) != 0)
			{
				LevelPointer -= 1;
				if (LevelPointer == -1)
				{
					LevelPointer = 10;
				}
			}
	else if (GetAsyncKeyState(VK_DOWN) != 0)
			{
				LevelPointer += 1;
				if (LevelPointer == 11)
				{
					LevelPointer = 0;
				}
			}
	else if (GetAsyncKeyState(VK_RETURN) != 0)
			{
				g_bQuitGame = false;
				switch(LevelPointer)
				{
					case 0:
						{
							currentLevel = 1;//Map1
							displayLevel();
							g_eGameState = S_GAME;
							break;
						}
					case 1:
						{
							currentLevel = 2;//Map2
							displayLevel();
							g_eGameState = S_GAME;
							break;
						}
					case 2:
						{
							currentLevel = 3;//Map3
							displayLevel();
							g_eGameState = S_GAME;
							break;
						}
					case 3:
						{
							currentLevel = 4;//Map4
							displayLevel();
							g_eGameState = S_GAME;
							break;
						}
					case 4:
						{
							currentLevel = 5;//Map5
							displayLevel();
							g_eGameState = S_GAME;
							break;
						}
					case 5:
						{
							currentLevel = 6;//Map6
							displayLevel();
							g_eGameState = S_GAME;
							break;
						}
					case 6:
						{
							currentLevel = 7;//Map7
							displayLevel();
							g_eGameState = S_GAME;
							break;
						}
					case 7: 
						{
							currentLevel = 8;//Map8
							displayLevel();
							g_eGameState = S_GAME;
							break;
						}
					case 8:
						{
							currentLevel = 9;//Map9
							displayLevel();
							g_eGameState = S_GAME;
							break;
						}
					case 9:
						{
							currentLevel = 10;//Map10
							displayLevel();
							g_eGameState = S_GAME;
							break;
						}
					case 10: g_eGameState = S_SPLASHSCREEN; break;
				}
			}
	Sleep(150);
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