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
COORD boxLocation;


char tmp_map[18][32];

char map[18][32] = {
	"###############################",
	"#                             #",
	"#                             #",
	"### ########### ##   ##########",
	"#   #                         #",
	"# # #### #  #           #     #",
	"# #      #  # ####  #   #  #  #",
	"# # ######  # #      ## #     #",
	"# #           ####  #      #  #",
	"# ###### ###         ##       #",
	"#          ######  ####### ####",
	"#                             #",
	"## ### ####      ###   ########",
	"#                             #",
	"#                             #",
	"#                             #",
	"#                             #",
	"###############################"
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

	boxLocation.X = 15;
	boxLocation.Y = 15;
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
    // Updating the location of the character based on the key press
    if (keyPressed[K_UP] && charLocation.Y > 0)
    {
		if (map[y-1][x] != '#')
		{
			Beep(1330, 30); 
			charLocation.Y--;
			if ((charLocation.Y - 1) == boxLocation.Y)
			{
				boxLocation.Y--;
			}
		}
		
    }
    if (keyPressed[K_LEFT] && charLocation.X > 0)
    {
		if (map[y][x-1] != '#')
		{
        Beep(1330, 30);
        charLocation.X--; 
		if ((charLocation.X - 1) == boxLocation.X)
	{
		boxLocation.X -= 1;
	}
		}
    }
    if (keyPressed[K_DOWN] && charLocation.Y < consoleSize.Y - 1)
    {
		if (map[y+1][x] != '#')
		{
        Beep(1330, 30);
        charLocation.Y++; 
		if((charLocation.Y + 1) == boxLocation.Y)
	{
		boxLocation.Y += 1;
	}

		}
    }
    if (keyPressed[K_RIGHT] && charLocation.X < consoleSize.X - 1)
    {
		if (map[y][x+1] != '#')
		{
        Beep(1330, 30);
        charLocation.X++; 
			if ((charLocation.X + 1) == boxLocation.X)
	{
		boxLocation.X += 1;
		
	}
		}
    }

	//update box location when pushed

	/*if (keyPressed[K_UP] && boxLocation.Y > 0 && charLocation.Y > 0)
	{
		if (((charLocation.Y - 1) == boxLocation.Y) && (map[y-1][x] != '#'))
		{
		boxLocation.Y--;
        Beep(1330, 30); 
        charLocation.Y--;
		}
	}
	if (keyPressed[K_LEFT] && charLocation.X > 0 && boxLocation.X > 0)
	{
		if (((charLocation.Y - 1) == boxLocation.Y) && (map[y][x-1] != '#'))
		{
		boxLocation.X--;
        Beep(1330, 30); 
        charLocation.X--;
		}
	}
	if (keyPressed[K_UP] && boxLocation.Y > 0 && charLocation.Y > 0)
	{
		if (((charLocation.Y - 1) == boxLocation.Y) && (map[y-1][x] != '#'))
		{
		boxLocation.Y--;
        Beep(1330, 30); 
        charLocation.Y--;
		}
	}
	if (keyPressed[K_UP] && boxLocation.Y > 0 && charLocation.Y > 0)
	{
		if (((charLocation.Y - 1) == boxLocation.Y) && (map[y-1][x] != '#'))
		{
		boxLocation.Y--;
        Beep(1330, 30); 
        charLocation.Y--;
		}
	}*/
	
	

	
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
    std::cout << (char)3;

	//render box
	gotoXY(boxLocation);
	colour(7);
	std::cout << (char)223;
	

}
