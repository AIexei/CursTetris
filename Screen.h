/*	Screen
 *  Gaming table's class 
 *  all drawn with the help of Painter
 *
 *  Copyright (c) Alexei Evlanov, 2015
 *  All rights reserved
 */

#pragma once
#pragma warning (disable : 4091)

#define PREVIEW_WINDOW_X 92
#define PREVIEW_WINDOW_Y 30

typedef struct CellType {
	bool Value;
	enum Color CellColor;
};


class Painter;
class Figures; 


class Screen {
public:
	// how many cells will be on the playing field 
	// in width and height
	enum {WIDTH = 10, HEIGHT = 15, CELL_SIZE = 8};

	Screen();

	void Draw (Painter);

	// check for a completed line and deleting
	// function return count of full lines in order to score
	int DeletingFullLines (int &Lines);
	
	// check collision with the wall or with pieces that have fallen
	bool Clash (Figures);

	// after falling figure ,its coordinates recorded in the Field
	void FallenFigure (Figures);

private:
	// this array describe our playing field
	CellType Field [HEIGHT][WIDTH];
};