// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>

double elapsedTime;
double deltaTime;
bool keyPressed[K_COUNT];
COORD charLocation;
COORD consoleSize;
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
			if( map[y - 1][x] != 'B') //if box(ascii char 66) not present
			{ 
                charLocation.Y--;
			} 
			else if ( map[y - 1][x] == 'B' && map[y-2][x] != (char)178 && map[y-2][x] != 'B')
			{
				map[y - 2][x] = 'B';
				charLocation.Y--;
				map[y - 1][x] = ' ';
				--y;
			}
			else if (map[y-1][x] != 'B' && map[y-2][x] != 'B' )
			{
				charLocation.Y--;
			}
		}
	}
    else if (keyPressed[K_LEFT] && charLocation.X > 0)
    {
		if (map[y][x-1] != (char)178)
	    {
			if( map[y][x-1] != 'B') //if box(ascii char 66) not present
			{ 
                charLocation.X--;
			} 
			else if ( map[y][x-1] == 'B' && map[y][x-2] != (char)178 && map[y][x-2] != 'B')
			{
				map[y][x-2] = 'B';
				charLocation.X--;
				map[y][x-1] = ' ';
				
			}
			else if (map[y][x-1] != 'B' && map[y][x-2] != 'B' )
			{
				charLocation.X--;
			}
		}
    }
    else if (keyPressed[K_DOWN] && charLocation.Y < consoleSize.Y - 1)
    {
		  if (map[y+1][x] != (char)178)
	   {
			if( map[y + 1][x] != 'B') //if box(ascii char 66) not present
			{ 
                charLocation.Y++;
			} 
			else if ( map[y+1][x] == 'B' && map[y+2][x] != (char)178 && map[y+2][x] != 'B')
			{
				map[y+2][x] = 'B';
				charLocation.Y++;
				map[y+1][x] = ' ';
				++y;
			}
			else if (map[y+1][x] != 'B' && map[y+2][x] != 'B' )
			{
				charLocation.Y++;
			}
		}
    }
    else if (keyPressed[K_RIGHT] && charLocation.X < consoleSize.X - 1)
    {
		if (map[y][x+1] != (char)178)
	    {
			if( map[y][x+1] != 'B') //if box(ascii char 66) not present
			{ 
                charLocation.X++;
			} 
			else if ( map[y][x+1] == 'B' && map[y][x+2] != (char)178 && map[y][x+2] != 'B')
			{
				map[y][x+2] = 'B';
				charLocation.X++;
				map[y][x+1] = ' ';
				
			}
			else if (map[y][x+1] != 'B' && map[y][x+2] != 'B' )
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
	// Resets the level if player hits the spacebar
	else if (keyPressed[K_SPACE])
	{
		charLocation.X = 28;
		charLocation.Y = 16;
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
    gotoXY(70, 0);
    colour(0x1A);
    std::cout << 1.0 / deltaTime << "fps" << std::endl;
  
    gotoXY(0, 0);
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
	"#                       ## ##  ##                         #",
	"#                       #   ##  #                         #",
	"#                       # B B B #                         #",
	"#      STAGE THREE       #  # B  #       Having Fun?      #",
	"#                       #   B B #                         #",
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
	"#                         # B BA              #           #",
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
			map[cols][rows] = Nmap[cols][rows];
		}
	}
}
void map9() {

	char Nmap[25][60] = {
	"###########################################################",
	"#       B     BBB         #                    B   BB  B  #",
	"#         #        ######          #######     BB   B     #",
	"# BBBBBB  ##########REKT############FACES##############   #",
	"# B       #       B######B         B######B           #   #",
	"# BBBBBB  #      B        B       B        B          #   #",
	"# B       #     B  B   B   B     B  B    B  B         #BBB#",
	"# BBBBBB  #     B          B     B          B         #   #",
	"#         #     B   BBBB   B     B  B    B  B         #   #",
	"# BBBBBB  #      B B    B B       B  BBBB  B          # B #",
	"#     B   #       BBBBBBBB         BBBBBBBB  BBBB######B B#",
	"#    B    ## ##############################BBBB    BB##  B#",
	"#   B     #                               #BBBBB B BB #   #",
	"#  B      ########################B#B B B##BBBBBB B   #   #",
	"# BBBBBB  #                       B B## B######### B  #   #",
	"#         #     ###############BBBB #  BB##     #BB BB#   #",
	"########  #     ########### S # B # BBB B## LOL #   B #   #",
	"#         #BB BB# LEVEL  ##   #   B    B ##     #   # #B B#",
	"# B######## B B #  NINE  ##   # BBBB  BB ##########BB #BB #",
	"#     B BB#B B B# LET'S  ## B #  B BB  BB### BB   #   #B B#",
	"######  BB# BBB #  GO    ##  B#   BB B B ##B  B       # B #",
	"#   B     # BB  ###########B B# ########### BBB####BBB#   #",
	"# #########  B  #         ##  ###  B    BB    ##  #B B#BB #",
	"#            B  #         #B        BB    B  B#   #B  # P #",
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
			map[cols][rows] = Nmap[cols][rows];
		}
	}
}
void map10() {

	char Nmap[25][60] = {
	"###########################################################",
	"#         #          #         B      #   B               #",
	"#               #  # # #######B # BBB ##B# ###########    #",
	"#  ##############  # # #     #  #B   B#   B#         #    #",
	"#  #    LAST    #  # # # ### #BB# BBB # #B## ####### #    #",
	"#  #    STAGE   #B # #   ##  #  #BB BB# B  # #     # #    #",
	"#  ##############B # #  ### ##BB##   ###B# # # ### # #    #",
	"#       # B        # #BBB##  #  ### ###    # # #P# # #    #",
	"#   ##  # ########## #   ### #BB#     # #B## #   # # #    #",
	"#BBB##    #  B       BB  ##B    #B###B# B  # ##### # #    #",
	"#  B   BB # B# # # #B BB  ####### ### # ####       # #    #",
	"#  ##B## B#   # B B B##  ####### BB B # B ########## #    #",
	"# B##  #B## BB # # B# #  ########   B # # #          #    #",
	"#B   B    #       B#  #  #  # B #  BB #    B #########    #",
	"## B ############    ##  #      ##B  B########            #",
	"##B B#JUST DO IT# ##     # BB#  #BB BB##    ##            #",
	"## B ####################### #BB# BB B#  # B ##           #",
	"#  ###B   B  B   B  BB     ###  #  B B#B ## B ##          #",
	"# ##B    BB   B BB B     B B#  B#B BB # B### B ######### ##",
	"# ##BBB################## B #   #B B B#  B ## B #    B    #",
	"#  #B  B         B    B #B  #   #BB BB### B ##B # #########",
	"## #B B########    BBB B# B #BBB#BB BBB ## B # B#         #",
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
			map[cols][rows] = Nmap[cols][rows];
		}
	}

}