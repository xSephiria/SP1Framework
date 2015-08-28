#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"
#include <string>
using std::string;

extern CStopWatch g_swTimer;
extern bool g_bQuitGame;

// Enumeration to store the control keys that your game will have
enum EKEYS
{
    K_UP,
    K_DOWN,
    K_LEFT,
    K_RIGHT,
    K_ESCAPE,
    K_SPACE,
	K_BACK,
	K_RETURN,

    K_COUNT
	
};



// Enumeration for the different screen states
enum EGAMESTATES
{
    S_MAINMENU,
    S_GAME,
	S_LEVELMENU,
	S_OPTIONS,
	S_INSTRUCTIONS,
	S_CHARSELECT,
	S_RECORD,
	S_HIGHSCORES,
	S_KEYNAME,
	S_GAMEOVER,
    S_COUNT
};


// struct for the game character
struct SGameChar
{
    COORD m_cLocation;
	char gamechar;
    bool  m_bActive;
};

void init        ( void );      // initialize your variables, allocate memory, etc
void getInput    ( void );      // get input from player
void update      ( double dt ); // update the game and the state of the game
void render      ( void );      // renders the current state of the game to the console
void shutdown    ( void );      // do clean up, free memory


void gameplay();            // gameplay logic
void moveCharacter();       // moves the character, collision detection, physics, etc
void processUserInput();    // checks if you should change states or do something else with the game, e.g. pause, exit
void clearScreen();         // clears the current screen and draw from scratch 

void renderGame();          // renders the game stuff
void renderMap();           // renders the map to the buffer first
void renderCharacter();     // renders the character into the buffer
void renderFramerate();     // renders debug information, frame rate, elapsed time, etc
void renderToScreen();      // dump the contents of the buffer to the screen, one frame worth of game



int playSong();
void lifepoint();
void loselife();
void gameover();


#endif // _GAME_H
