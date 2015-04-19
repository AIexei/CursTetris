#include <glut.h>
#include "Painter.h"

void Painter::Rectangle (int x1, int y1, int x2, int y2, Color MyColor) {
	// say that we will draw quadrilateral
	SetColor (MyColor);
	glBegin (GL_QUADS);
		glVertex2f (x1, y1);
		glVertex2f(x2, y1);
		glVertex2f(x2, y2);
		glVertex2f(x1, y2);
	glEnd();
}


void Painter::SetColor (Color MyColor) {
	const RGB Colors [] = 
	{
		{0.9, 0, 0},           // red
		{0, 0.75, 1},        // deep sky blue
		{1, 0.08, 0.58},     // deep pink
		{0, 1, 1},           // cyan
		{1, 0.5, 0},         // dark orange
		{1, 1, 0},           // yellow
		{1, 0.5, 0.14},      // chocolate
		{1, 0 , 1}, // magenta
		{0, 1, 0},   // green
		{1.0, 1.0, 1.0}	     // white
	};

	// set the brush color
	glColor3f (Colors [MyColor].Red,
			   Colors [MyColor].Green,
			   Colors [MyColor].Blue);
}