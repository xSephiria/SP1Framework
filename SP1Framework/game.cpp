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

void map1();
void map2();

char map[18][32] = {0};

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
    charLocation.X = 9;
    charLocation.Y = 3;
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
    // Updating the location of the character based on the key press
	if ( keyPressed[K_UP] && charLocation.Y > 0 )
    {
	   if (map[y-1][x] != '#')
	   {
			if( map[y - 1][x] != 'B') //if box(ascii char 66) not present
			{ 
                charLocation.Y--;
			} 
			else if ( map[y - 1][x] == 'B' && map[y-2][x] != '#' && map[y-2][x] != 'B')
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

    if (keyPressed[K_LEFT] && charLocation.X > 0)
    {
		if (map[y][x-1] != '#')
	    {
			if( map[y][x-1] != 'B') //if box(ascii char 66) not present
			{ 
                charLocation.X--;
			} 
			else if ( map[y][x-1] == 'B' && map[y][x-2] != '#' && map[y][x-2] != 'B')
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
    if (keyPressed[K_DOWN] && charLocation.Y < consoleSize.Y - 1)
    {
		  if (map[y+1][x] != '#')
	   {
			if( map[y + 1][x] != 'B') //if box(ascii char 66) not present
			{ 
                charLocation.Y++;
			} 
			else if ( map[y+1][x] == 'B' && map[y+2][x] != '#' && map[y+2][x] != 'B')
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
    if (keyPressed[K_RIGHT] && charLocation.X < consoleSize.X - 1)
    {
		if (map[y][x+1] != '#')
	    {
			if( map[y][x+1] != 'B') //if box(ascii char 66) not present
			{ 
                charLocation.X++;
			} 
			else if ( map[y][x+1] == 'B' && map[y][x+2] != '#' && map[y][x+2] != 'B')
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
    if (keyPressed[K_ESCAPE])
        g_quitGame = true;    
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

	
}
void map1()
{
	char Nmap[18][32] ={
	"############################",
	"#                          #",
	"#        @                 #",
	"#                 B        #",
	"#                 B        #",
	"#  B                       #",
	"#         B                #",
	"############################"};

	for (int cols = 0; cols < 18; cols++)
	{
		for (int rows = 0; rows < 32; rows++)
		{
			map[cols][rows] = Nmap[cols][rows];
		}
	}
	
}
void map2()
{
	char Nmap[18][32] ={
	"############################",
	"#           @              #",
	"###########   ##############",
	"#          BBB             #",
	"#                          #",
	"#                          #",
	"#                          #",
	"############################"};

	for (int cols = 0; cols < 18; cols++)
	{
		for (int rows = 0; rows < 32; rows++)
		{
			map[cols][rows] = Nmap[cols][rows];
		}
	}
}