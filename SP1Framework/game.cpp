// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

double elapsedTime;
double deltaTime;
bool keyPressed[K_COUNT];
bool something = false;
COORD charLocation;
COORD consoleSize;
double bouncetime;
int currentLevel;

char map[25][60] = {0};

void init()
{
	
    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);

    SetConsoleTitle(L"SP1 Framework");

    // Sets the console size, this is the biggest so far.
    setConsoleSize(79,28);

    // Get console width and height
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

    /* get the number of character cells in the current buffer */ 
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    consoleSize.X = csbi.srWindow.Right + 1;
    consoleSize.Y = csbi.srWindow.Bottom + 1;

    // set the character to be in the center of the screen.
    charLocation.X = 28;
    charLocation.Y = 16;
    elapsedTime = 0.0;

	
}
void shutdown()
{
    // Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}
void getInput()
{    
    keyPressed[K_UP] = isKeyPressed(VK_UP);
    keyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
    keyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
    keyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
	keyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
    keyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
}
void update(double dt)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;
	int x=charLocation.X;
	int y=charLocation.Y;
	
    // Updating the location of the character based on the key press
	if ( keyPressed[K_UP] && charLocation.Y > 0 )
    {
	   if (map[y-1][x] != (char)178)
	   {
			if( map[y - 1][x] != (char)254) //if box not present
			{ 
                charLocation.Y--;
				
			} 
			else if ( map[y - 1][x] == (char)254 && map[y-2][x] != (char)178 && map[y-2][x] != (char)254)
			{
				map[y - 2][x] = (char)254;
				charLocation.Y--;
				map[y - 1][x] = ' ';
				
			}
			else if (map[y-1][x] != (char)254 && map[y-2][x] != (char)254 )
			{
				charLocation.Y--;
				
			}
		}
	}
    else if (keyPressed[K_LEFT] && charLocation.X > 0)
    {
		if (map[y][x-1] != (char)178)
	    {
			if( map[y][x-1] != (char)254) //if box(ascii char 66) not present
			{ 
                charLocation.X--;
				
			} 
			else if ( map[y][x-1] == (char)254 && map[y][x-2] != (char)178 && map[y][x-2] != (char)254)
			{
				map[y][x-2] = (char)254;
				charLocation.X--;
				map[y][x-1] = ' ';
			
				
			}
			else if (map[y][x-1] != (char)254 && map[y][x-2] != (char)254 )
			{
				charLocation.X--;
				
			}
		}
    }
    else if (keyPressed[K_DOWN] && charLocation.Y < consoleSize.Y - 1)
    {
		  if (map[y+1][x] != (char)178)
	   {
			if( map[y + 1][x] != (char)254) //if box(ascii char 66) not present
			{ 
                charLocation.Y++;
				
			} 
			else if ( map[y+1][x] == (char)254 && map[y+2][x] != (char)178 && map[y+2][x] != (char)254)
			{
				map[y+2][x] = (char)254;
				charLocation.Y++;
				map[y+1][x] = ' ';
			
			}
			else if (map[y+1][x] != (char)254 && map[y+2][x] != (char)254 )
			{
				charLocation.Y++;
				
			}
		}
    }
    else if (keyPressed[K_RIGHT] && charLocation.X < consoleSize.X - 1)
    {
		if (map[y][x+1] != (char)178)
	    {
			if( map[y][x+1] != (char)254) //if box(ascii char 66) not present
			{ 
                charLocation.X++;
			
			} 
			else if ( map[y][x+1] == (char)254 && map[y][x+2] != (char)178 && map[y][x+2] != (char)254)
			{
				map[y][x+2] = (char)254;
				charLocation.X++;
				map[y][x+1] = ' ';
			
				
			}
			else if (map[y][x+1] != (char)254 && map[y][x+2] != (char)254 )
			{
				charLocation.X++;
			
			}
		}
	}

    // quits the game if player hits the escape key
    else if (keyPressed[K_ESCAPE])
	{
        g_quitGame = true;    
		charLocation.X = 28;
		charLocation.Y = 16;
	}
	
	// restart the game if player hit space
	if (keyPressed[K_SPACE])
	{
		charLocation.X = 28;
		charLocation.Y = 16;
		displayLevel();
	}
	
	if (map[y][x] == '@')
	{
		charLocation.X = 28;
		charLocation.Y = 16;
		levelMenu();
		displayLevel();
	}
}
void render()
{
    // clear previous screen
    colour(0x0F);
    cls();
    //render test screen code (not efficient at all)
    const WORD colors[] =   {
	                        0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
	                        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
	                        };


	/*for (int i = 0; i < 12; ++i)
	{
		//gotoXY(3*i,i+1);
		colour(colors[i]);
		std::cout << std::endl;
		std::cout << "LOLOL";
	}*/
	for(int i = 0; i < 25; i++) 
	{

		colour(0x0B);
		printf("%s\n",map[i] );
	}
			

    // render time taken to calculate this frame
    gotoXY(70, 25);
    colour(0x1A);
    std::cout << 1.0 / deltaTime << "fps" << std::endl;
  
    gotoXY(0, 25);
    colour(0x59);
    std::cout << elapsedTime << "secs" << std::endl;

    // render character
    gotoXY(charLocation);
    colour(0x0C);
    std::cout << (char)1;

	
}
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

	for (int cols = 0; cols < 26; cols++)
	{
		for (int rows = 0; rows <61; rows++)
		{
			if (Nmap[cols][rows] == '#')
			{
				Nmap[cols][rows] = (char)178;
			}
			if (Nmap[cols][rows] == 'B')
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


	for (int cols = 0; cols < 26; cols++)
	{
		for (int rows = 0; rows < 61; rows++)
		{
			if (Nmap[cols][rows] == '#')
			{
				Nmap[cols][rows] = (char)178;
			}
			if (Nmap[cols][rows] == 'B')
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

	for (int cols = 0; cols < 26; cols++)
	{
		for (int rows = 0; rows < 61; rows++)
		{
			if (Nmap[cols][rows] == '#')
			{
				Nmap[cols][rows] = (char)178;
			}
			if (Nmap[cols][rows] == 'B')
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

	for (int cols = 0; cols < 26; cols++)
	{
		for (int rows = 0; rows < 61; rows++)
		{
			if (Nmap[cols][rows] == '#')
			{
				Nmap[cols][rows] = (char)178;
			}
			if (Nmap[cols][rows] == 'B')
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

		for (int cols = 0; cols < 26; cols++)
	{
		for (int rows = 0; rows < 61; rows++)
		{
			if (Nmap[cols][rows] == '#')
			{
				Nmap[cols][rows] = (char)178;
			}
			if (Nmap[cols][rows] == 'B')
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
	"#                      # B ###       #B B  ###            #",
	"#     Stage 6          # B  #        ## ####              #",
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

	for (int cols = 0; cols < 26; cols++)
	{
		for (int rows = 0; rows < 61; rows++)
		{
			if (Nmap[cols][rows] == '#')
			{
				Nmap[cols][rows] = (char)178;
			}
			if (Nmap[cols][rows] == 'B')
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

	for (int cols = 0; cols < 26; cols++)
	{
		for (int rows = 0; rows < 61; rows++)
		{
			if (Nmap[cols][rows] == '#')
			{
				Nmap[cols][rows] = (char)178;
			}
			if (Nmap[cols][rows] == 'B')
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
	"#          ##  #  #####UMAD?#BBB#B # B B###BRO?### B B #  #",
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

	for (int cols = 0; cols < 26; cols++)
	{
		for (int rows = 0; rows < 61; rows++)
		{
			if (Nmap[cols][rows] == '#')
			{
				Nmap[cols][rows] = (char)178;
			}
			if (Nmap[cols][rows] == 'B')
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
	for (int cols = 0; cols < 26; cols++)
	{
		for (int rows = 0; rows <61; rows++)
		{
			if (Nmap[cols][rows] == '#')
			{
				Nmap[cols][rows] = (char)178;
			}
			if (Nmap[cols][rows] == 'B')
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

	for (int cols = 0; cols < 26; cols++)
	{
		for (int rows = 0; rows < 61; rows++)
		{
			if (Nmap[cols][rows] == '#')
			{
				Nmap[cols][rows] = (char)178;
			}
			if (Nmap[cols][rows] == 'B')
			{
				Nmap[cols][rows] = (char)254;
			}
			map[cols][rows] = Nmap[cols][rows];
		}
	}
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
							cout << "What character do you want?\n 1 for smiley, 2 for hearts, 3 for invisible.";
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