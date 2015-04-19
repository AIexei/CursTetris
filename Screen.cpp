#include "Screen.h"
#include "Painter.h"
#include "Figures.h"

Screen::Screen () {
	// at the beginning of the game our field empty
	for (int y = 0; y < HEIGHT; ++y)
		for (int x = 0; x < WIDTH; ++x) {
			Field [y][x].Value = false;
			Field [y][x].CellColor = WHITE;
		}
}


void Screen::Draw (Painter MyPainter) {
	for (int y = 0; y < HEIGHT; ++y) {
		for (int x = 0; x < WIDTH; ++x) {
			if (Field [y][x].Value) {
				MyPainter.Rectangle (x * CELL_SIZE + 1,
									 y * CELL_SIZE + 1,
									 ((x + 1) * CELL_SIZE) - 1, 
									 ((y + 1) * CELL_SIZE) - 1,
									 Field [y][x].CellColor);
			}
		}
	}
}


int Screen::DeletingFullLines () {
	int CountFullLines = 0;

	for (int y = 0; y < HEIGHT; ++y) {
		bool IsFull = true;

		for (int x = 0; x < WIDTH; ++x) {
			if (! Field [y][x].Value) {
				IsFull = false;
				break;
			}
		}

		if (IsFull) {
			CountFullLines++;
			// variable Above means line, which is above the full line
			for (int Above = y - 1; Above >= 0; --Above)
				for (int x = 0; x < WIDTH; ++x) 
					Field [Above + 1][x] = Field [Above][x];

			for (int x = 0; x < WIDTH; ++x) 
				Field [0][x].Value = false;
		}
	}

	return CountFullLines;
}


bool Screen::Clash (Figures MyFigure) {
	for (int y = 0; y < 4; ++y) {
		for (int x = 0; x < 4; ++x) {
			if (MyFigure.FigureArea (x, y)) {
				// these are coordinates of the area of our figure on the field
				int Field_x = x + MyFigure.Get_x ();
				int Field_y = y + MyFigure.Get_y ();

				// checking for collisions with the walls and the fallen figures
				if (Field_x < 0 ||
					Field_x >= WIDTH ||
					Field_y < 0 || // ????
					Field_y >= HEIGHT) return true;

				if (Field [Field_y][Field_x].Value) 
					return true;
			}
		}
	}

	return false;
}


void Screen::FallenFigure (Figures MyFigure) {
	for (int y = 0; y < 4; ++y) 
		for (int x = 0; x < 4; ++x) {
			// these are coordinates of the area of our figure on the field
			int Field_x = x + MyFigure.Get_x ();
			int Field_y = y + MyFigure.Get_y ();

			if (Field_x >= 0 ||
				Field_x < WIDTH ||
				Field_y >= 0 ||
				Field_y < HEIGHT) {					
					// if in the field cell is empty, and figure's cell is not empty,
					// this cell are assigned properties of the figure's cell
					if ((! Field [Field_y][Field_x].Value) && MyFigure.FigureArea (x,y)) {
						Field [Field_y][Field_x].CellColor = (enum Color) MyFigure.FigureName;
						Field [Field_y][Field_x].Value = true;
					}
			}
		}
}