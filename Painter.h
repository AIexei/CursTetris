/*  Painter
 *	this class is intended only for drawing any graphic objects
 */

#pragma once
#pragma warning (disable : 4091)

// define the structure "RGB" 
typedef struct RGB {
	float Red; 
	float Green;
	float Blue;
};


enum Color {RED, SKY, 
			PINK, BLUE, 
		    ORANGE, YELLOW, 
			CHOCOLATE, MAGENTA,
			GREEN, WHITE, 
			VIOLET, OLIVE};
//  add new colors


class Painter {
public:
	void SetColor (Color);

	// drawing rectangle on two opposite points
	void Rectangle (int x1, int y1, int x2, int y2, Color);
	
	// drawing an unfilled rectangle
	void EmptyRectangle (int x1, int y1, int x2, int y2, Color);
	
	// drawing line
	void Line (int x1, int y1, int x2, int y2, Color);
	void PrintText (int x, int y, char *text, Color);
	//char *IntToStr (int value);
};