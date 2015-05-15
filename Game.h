/*	Game
 *	This class brings together all previous classes
 */

#pragma once

// include classes Screen and Figures 
// because class Game has these types of variables
#include "Screen.h"
#include "Figures.h"

class Painter;


class Game {
public: 
	enum Direction { UP, DOWN, LEFT, RIGHT};
	enum Mode {CLASSIC = 7, ARCADE = 13};

	Game (Mode);

	// function to calculate the level
	// figures fall quickly on each of 7 levels
	int GetLevel ();

	// procedure draws a box, and a figure which falls
	void Draw (Painter);

	// function that changes the game over time
	void Tick ();

	// function to start a new game
	void Start ();

	// function, which processes the pressing
	void KeyEvent (Direction);

	//...
	char* ShowLevel ();
	char* ShowLines ();
	char* ShowScore ();
	char* ShowHighScore ();

private:	
	int Score;
	int HighScore;
	int Level;
	int Lines;

	Mode GameMode;
	Screen GameScreen;
	Figures CurrentFigure;
	Figures NextFigure;
};