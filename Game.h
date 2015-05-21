/*	Game
 *	This class brings together all previous classes
 *
 *  Copyright (c) Alexei Evlanov, 2015
 *  All rights reserved
 */

#pragma once

// include classes Screen and Figures 
// because class Game has these types of variables
#include "Screen.h"
#include "Figures.h"
#include <fstream>

class Painter;


class Game {
public: 
	enum Direction { UP, DOWN, LEFT, RIGHT};
	enum Mode {CLASSIC = 7, ARCADE = 16, FRENZY};

	// game has 2 modes. 
	// these are Arcade and Classic
	Game (Mode);

	// function to calculate the level
	// figures fall quickly on each of 7 levels
	int GetLevel ();

	// procedure draws a box, and a figure which falls
	void Draw (Painter);

	// function that changes the game over time
	void Tick ();

	// function to start a new game
	void Start (Mode);
	void Start ();

	// function, which processes the pressing
	void KeyEvent (Direction);

	// this function write the results to file
	void SaveScore();

	// these functions allow you to get information about the game
	char* ShowLevel ();
	char* ShowLines ();
	char* ShowScore ();
	char* ShowHighScore ();

private:	
	std::fstream ScoreFile;

	int Score;
	int HighScoreClassic;
	int HighScoreArcade;
	int Level;
	int Lines;

	Mode GameMode;
	Screen GameScreen;
	Figures CurrentFigure;
	Figures NextFigure;
};