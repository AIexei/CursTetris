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

	Game ();

	// function to calculate the level
	// figures fall quickly on each of 7 levels
	int GetLevel ();

	// procedure draws a box, and a figure which falls
	void Draw (Painter);

	// function that changes the game over time
	void Tick ();

	// function to start a new game
	void Restart ();

	// function, which processes the pressing
	void KeyEvent (Direction);

private:		
	int Score;
	int HighScore;
	int Level;

	Screen GameScreen;
	Figures CurrentFigure;
};