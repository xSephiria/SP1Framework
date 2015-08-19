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
COORD boxLocation;
COORD box2Location;
COORD consoleSize;


char tmp_map[18][32];

char map[18][32] = {
	"                               ",
	"                               ",
	"                               ",
	"                               ",
	"                               ",
	"        # P#   # ##X#          ",
	"         #  #     # #          ",
	"         #  #     # #          ",
	"         #  ##   ## #          ",
	"       ### ### B    #          ",
	"       #         #  ###        ",
	"       # ##############        ",
	"       #              #        ",
	"       #B####     ### #        ",
	"       #X#  #     #   #        ",
	"       ###  #     #####        ",
	"            #  S  #            ",
	"            #######            ",
	};

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
    charLocation.X = 15;
    charLocation.Y = 16;
    elapsedTime = 0.0;

	// set box.
	boxLocation.X = 15;
	boxLocation.Y = 14;
	elapsedTime = 0.0;
	box2Location.X = 16;
	box2Location.Y = 14;
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
    keyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
}

void update(double dt)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;
	int x=charLocation.X;
	int y=charLocation.Y;
	int a=boxLocation.X;
	int b=boxLocation.Y;
	int c=box2Location.X;
	int d=box2Location.Y;
    // Updating the location of the character based on the key press
    if (keyPressed[K_UP] && charLocation.Y > 0)
    {
		if (map[y-1][x] != '#' && charLocation.X != boxLocation.X && charLocation.Y-1 != boxLocation.Y )
		{
			Beep(1330, 30);
			charLocation.Y--;	
		} 
			else
				{
					if (charLocation.Y-1 == boxLocation.Y && charLocation.X == boxLocation.X)
					{
						if (map[b-1][a] != '#' && boxLocation.X != box2Location.X && boxLocation.Y-1 != box2Location.Y) //if the box in front is not a # and not behind box2
					{
						Beep(1330, 30);
						boxLocation.Y--;
						charLocation.Y--;
					}
					else
					{
						if (boxLocation.Y-1 == box2Location.Y && boxLocation.X == box2Location.X) //if box 1 is behind box2
						{
							if (map[d-1][c] != ' ')
							{
								Beep(1330, 30);
								boxLocation.Y--;
								charLocation.Y--;
							}
						}
						else if (map[b-1][a] != '#') //if box1 in front is not a #
						{	
							Beep(1330, 30);
							boxLocation.Y--;
							charLocation.Y--;
						}
					}
					}
					else if (map[y-1][x] != '#')
					{
						charLocation.Y--;
					}
				}
	}

    if (keyPressed[K_LEFT] && charLocation.X > 0)
    {
		if (map[y][x-1] != '#' && charLocation.X - 1 != boxLocation.X && charLocation.Y != boxLocation.Y )
		{
        Beep(1330, 30);
        charLocation.X--; 
		}
		else
		{
			if (charLocation.Y == boxLocation.Y && charLocation.X - 1 == boxLocation.X)
			{
				if (map[b][a-1] != '#' && boxLocation.X - 1 != box2Location.X && boxLocation.Y != box2Location.Y) //if the box in front is not a # and not behind box2
					{
						Beep(1330, 30);
						boxLocation.X--;
						charLocation.X--;
					}
					else
					{
						if (boxLocation.Y == box2Location.Y && boxLocation.X-1 == box2Location.X) //if box 1 is behind box2
						{
							if (map[d][c-1] != ' ')
							{
								Beep(1330, 30);
								boxLocation.X--;
								charLocation.X--;
							}
						}
						else if (map[b][a-1] != '#') //if box1 in front is not a #
						{	
							Beep(1330, 30);
							boxLocation.X--;
							charLocation.X--;
						}
					}
			}
			else if (map[y][x-1] != '#')
			{
				charLocation.X--;
			}
		}


    }
    if (keyPressed[K_DOWN] && charLocation.Y < consoleSize.Y - 1)
    {
		if (map[y+1][x] != '#' && charLocation.X != boxLocation.X && charLocation.Y+1 != boxLocation.Y )
		{
        Beep(1330, 30);
        charLocation.Y++; 
		}
		else
		{
			if (charLocation.Y+1 == boxLocation.Y && charLocation.X == boxLocation.X)
			{
				if (map[b+1][a] != '#' && boxLocation.X  != box2Location.X && boxLocation.Y + 1 != box2Location.Y) 
					{
						Beep(1330, 30);
						boxLocation.Y++;
						charLocation.Y++;
					}
					else
					{
						if (boxLocation.Y+1 == box2Location.Y && boxLocation.X == box2Location.X) 
						{
							if (map[d+1][c] != ' ')
							{
								Beep(1330, 30);
								boxLocation.Y++;
								charLocation.Y++;
							}
						}
						else if (map[b+1][a] != '#')
						{	
							Beep(1330, 30);
							boxLocation.Y++;
							charLocation.Y++;
						}
					}
			}
			else if (map[y+1][x] != '#')
			{
				charLocation.Y++;
			}
		}
    }

    if (keyPressed[K_RIGHT] && charLocation.X < consoleSize.X - 1)
    {
		if (map[y][x+1] != '#' && charLocation.X + 1 != boxLocation.X && charLocation.Y != boxLocation.Y ) // if the char in front is not # and not behind a box
		{
        Beep(1330, 30);
        charLocation.X++; 
		}
		else
		{
			if (charLocation.Y == boxLocation.Y && charLocation.X+1 == boxLocation.X) // if the char is behind a box
			{
					if (map[b][a+1] != '#' && boxLocation.X + 1 != box2Location.X && boxLocation.Y != box2Location.Y) //if the box in front is not a # and not behind box2
					{
						Beep(1330, 30);
						boxLocation.X++;
						charLocation.X++;
					}
					else
					{
						if (boxLocation.Y == box2Location.Y && boxLocation.X+1 == box2Location.X) //if box 1 is behind box2
						{
							if (map[d][c+1] != ' ')
							{
								Beep(1330, 30);
								boxLocation.X++;
								charLocation.X++;
							}
						}
						else if (map[b][a+1] != '#') //if box1 in front is not a #
						{	
							Beep(1330, 30);
							boxLocation.X++;
							charLocation.X++;
						}
					}
			}
			else if (map[y][x+1] != '#') // if the char in front is not a #
			{
				charLocation.X++;
			}
		}
	}
	
    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
        g_quitGame = true;    
}


void render()
{
	
    // clear previous screen
    colour(0x0F);
    cls();

    //render the game

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

	for(int i = 0; i < 18; i++) {

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

	gotoXY(boxLocation);
    colour(0x0C);
    std::cout << (char)219;
	gotoXY(box2Location);
    colour(0x0C);
    std::cout << (char)219;

}

