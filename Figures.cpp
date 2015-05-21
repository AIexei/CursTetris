#include "Figures.h"
#include "Painter.h"
#include "Screen.h"


Figures::Figures (Name MyName) {
	FigureName = MyName;
	x = 3;
	y = 0;
	RotateDirection = 0;
}


void Figures::PriorShow (Painter MyPainter) {
	Color FigureColor = (enum Color) FigureName;

	for (int Area_y = 0; Area_y < 4; ++Area_y)
		for (int Area_x = 0; Area_x < 4; ++Area_x) {
			if (FigureArea(Area_x, Area_y)) {
				MyPainter.Rectangle (Area_x * Screen::CELL_SIZE + PREVIEW_WINDOW_X + 1,
									 Area_y * Screen::CELL_SIZE + PREVIEW_WINDOW_Y + 1,
									 (Area_x + 1) * Screen::CELL_SIZE + PREVIEW_WINDOW_X - 1,
									 (Area_y + 1) * Screen::CELL_SIZE + PREVIEW_WINDOW_Y - 1,
									 FigureColor);
			}
		}
}


void Figures::DrawFigure (Painter MyPainter) {
	Color FigureColor = (enum Color) FigureName;

	for (int Area_y = 0; Area_y < 4; ++Area_y)
		for (int Area_x = 0; Area_x < 4; ++Area_x) {
			if (FigureArea(Area_x, Area_y)) {
				MyPainter.Rectangle ((Area_x + x) * Screen::CELL_SIZE + 1,
									 (Area_y + y) * Screen::CELL_SIZE + 1,
									 (Area_x + x + 1) * Screen::CELL_SIZE - 1,
									 (Area_y + y + 1) * Screen::CELL_SIZE - 1,
									 FigureColor);
			}
		}
}


bool Figures::FigureArea (int Area_x, int Area_y) {
	// graphic description
	const char *Shapes [][4] = 
	{
		// O
		{
			"    ",
			" 00 ",
			" 00 ",
			"    "
		}, 

		// S
		{
			" 0  ",
			" 00 ",
			"  0 ",
			"    ",
		},

		// T
		{
			"    ",
			" 000",
			"  0 ",
			"    "
		},

		// Z
		{
			"  0 ",
			" 00 ",
			" 0  ",
			"    "
		},

		// I
		{
			"  0 ",
			"  0 ",
			"  0 ",
			"  0 "
		},

		// J
		{
			"  0 ",
			"  0 ",
			" 00 ",
			"    "
		},

		// L
		{
			" 0  ",
			" 0  ",
			" 00 ",
			"    "
		},

		//  Ñ
		{
			" 00 ",
			" 0  ",
			" 00 ",
			"    "
		},

		// X
		{
			"  0 ",
			" 000",
			"  0 ",
			"    "
		},

		// Q
		{
			"    ",
			" 0  ",
			" 00 ",
			"    "
		},

		// F
		{
			"  00",
			" 00 ",
			" 0  ",
			"    "
		},
		
		// P
		{
			"    ",
			" 00 ",
			" 000",
			"    "
		},

		// B
		{
			"    ",
			" 000",
			" 00 ",
			"    "
		},

		// M
		{
			" 0  ",
			" 000",
			" 0  ",
			"    "
		},

		// R
		{
			"  0 ",
			" 000",
			" 0  ",
			"    "
		},

		// A
		{
			" 0  ",
			" 000",
			"  0 ",
			"    "
		}

	};


	// new coordinates, which are obtained as a result of rotation
	int new_x;
	int new_y;

	switch (RotateDirection) {
	// home position
	case 0 : new_x = Area_x; 
			 new_y = Area_y;
		break;

	// right
	case 1 : new_x = Area_y;
			 new_y = 3 - Area_x;
		break;

	// bottom
	case 2: new_x = 3 - Area_x;
			new_y = 3 - Area_y;
		break;

	// left
    case 3 : new_x = 3 - Area_y;
			 new_y = Area_x;
	    break;
	}

	return (Shapes [FigureName][new_y][new_x] != ' ');
}


void Figures::Move (int dx, int dy) {
	x += dx;
	y += dy;
}


void Figures::Rotate (){
	// go right by default
	RotateDirection += 1;

	// take the remainder of the division by 4 in order to avoid errors
	RotateDirection %= 4;
}


int Figures::Get_x () {
	return x;
}


int Figures::Get_y () {
	return y;
}