/*	Figures
 *  class figures that will fall during a game 
 *
 *  Copyright (c) Alexei Evlanov, 2015
 *  All rights reserved
 */

#pragma once

class Painter;

class Figures {
public:
	// figures names that corresponding to a figures view
	enum Name {O, S, T, Z, I, J, L, C, X, Q, F, P, B, M, R, A};

	Name FigureName;

	Figures (Name);

	void PriorShow (Painter);
	void DrawFigure (Painter);

	// dx and dy are offset in x and in y
	void Move (int dx, int dy);

	void Rotate (); 	

	// in this function coordinates Area_x and Area_y refer to the figure
	// not to the field
	bool FigureArea (int Area_x, int Area_y);

	int Get_x ();
	int Get_y ();

private:
	//Name FigureName;

	// coordinates figures are measured from the upper left corner
	// this coordinates refet to the field
	int x;
	int y;

	// 0 means home position, 1 - right
	// 2 - bottom, 3 - left
	int RotateDirection;
};