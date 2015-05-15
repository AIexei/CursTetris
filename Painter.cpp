#include <glut.h>
#include <string>
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
		{0.90, 0.00, 0.00},     // red
		{0.00, 0.75, 1.00},     // deep sky blue
		{1.00, 0.08, 0.58},     // deep pink
		{0.00, 1.00, 1.00},     // cyan
		{1.00, 0.50, 0.00},     // dark orange
		{1.00, 1.00, 0.00},     // yellow
		{1.00, 0.50, 0.14},     // chocolate
		{1.00, 0.00, 1.00},		// magenta
		{0.00, 1.00, 0.00},		// green
		{1.00, 1.00, 1.00},     // white
		{0.58, 0.00, 0.82},     // dark violet
		{0.75, 1.00, 0.24}		// olive
	};

	// set the brush color
	glColor3f (Colors [MyColor].Red,
			   Colors [MyColor].Green,
			   Colors [MyColor].Blue);
}


void Painter::EmptyRectangle (int x1, int y1, int x2, int y2, Color LineColor) {
	glBegin (GL_LINES);
	SetColor (LineColor);
	
	glVertex2d (x1, y1);
	glVertex2d (x1, y2);

	glVertex2d (x1, y2);
	glVertex2d (x2, y2);

	glVertex2d (x2, y2);
	glVertex2d (x2, y1);

	glVertex2d (x2, y1);
	glVertex2d (x1, y1);
	
	glEnd();
}


void Painter::Line (int x1, int y1, int x2, int y2, Color LineColor) {
	glBegin (GL_LINES);
	SetColor (LineColor);
	glVertex2d (x1, y1);
	glVertex2d (x2, y2);
	glEnd ();
}


void Painter::PrintText (int x, int y, char *text, Color TextColor) {
	glRasterPos2d (x, y);
	SetColor (TextColor);

	for (char *s = text; *s != '\0'; s++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *s);
	}
}