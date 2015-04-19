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

// днаюбхрэ жберю дн 10 ьрсй
enum Color {RED, WHITE, 
			PINK, BLUE, 
		    GREEN, YELLOW, 
			LIME, BLACK,
			VINOUS, GREY};


class Painter {
public:
	void SetColor (Color);

	// drawing rectangle on two opposite points
	void Rectangle (int x1, int y1, int x2, int y2, Color);
};