#include <glut.h>
#include <time.h>
#include <algorithm>
#include <string.h>
#include "Painter.h"
#include "Game.h"


#define RADIX 10


Game Tetris;
Painter MyPainter;
bool Pause = false;


void Display () {
	// paint the background
	glClear (GL_COLOR_BUFFER_BIT);

	MyPainter.PrintText (PREVIEW_WINDOW_X, 20, "The following figure", RED);
	MyPainter.PrintText (PREVIEW_WINDOW_X, 75, Tetris.ShowLevel(), RED);
	MyPainter.PrintText (PREVIEW_WINDOW_X, 87, Tetris.ShowLines(), RED);
	MyPainter.PrintText (PREVIEW_WINDOW_X, 99, Tetris.ShowScore(), RED);
	MyPainter.PrintText (PREVIEW_WINDOW_X, 111, Tetris.ShowHighScore(), RED);

	Tetris.Draw (MyPainter);

	glutSwapBuffers();
}


void Initialize () {
	// set a background color
	glClearColor (0, 0, 0, 1);

	// set a type of matrix
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glOrtho (0, (Screen::WIDTH * Screen::CELL_SIZE) * 1.75, (Screen::HEIGHT * Screen::CELL_SIZE) , 0, -1, 1);
}


// this function is needed for animation (game)
void Timer (int) {
	Tetris.Tick ();
	Display ();
	if (!Pause)
	glutTimerFunc (30 * (10 - Tetris.GetLevel ()), Timer, 0);
}


// this function has 4 arguments
// the second argument indicates the condition of the mouse (pressed or not pressed)
// and the third and fourth arguments are coordinates of the mouse
void MousePressed (int Button, int State, int x, int y) {
	//...
}


// this function has 3 arguments 
// the first is the key and the rest are coordinates of the mouse
void KeyPressed (int Key, int x, int y) {
	switch (Key) {
	case GLUT_KEY_LEFT :
		if (!Pause)
			Tetris.KeyEvent (Game::LEFT);
		break;
	case GLUT_KEY_RIGHT :
		if (!Pause)
			Tetris.KeyEvent (Game::RIGHT);
		break;
	case GLUT_KEY_UP :
		if (!Pause)	
			Tetris.KeyEvent (Game::UP);
		break;
	case GLUT_KEY_DOWN :
		if (!Pause) 
			Tetris.KeyEvent (Game::DOWN);
		break;
	case GLUT_KEY_F1 :
		Pause = !Pause;
		Timer(0);
		break;
	}

	Display ();
}


int main (int argc, char  **argv) {
	// initialize
	srand (time (NULL)); 
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (5 * Screen::WIDTH * Screen::CELL_SIZE * 1.75, 5 * Screen::HEIGHT * Screen::CELL_SIZE);
	glutInitWindowPosition (400, 50);
	glutCreateWindow ("TETRIS");
	glutDisplayFunc (Display);
	glutSpecialFunc (KeyPressed);
	glutMouseFunc (MousePressed);
	Timer (0);
	Initialize ();
	glutMainLoop ();
	return 0;
}

// меню. 2 режима игры. 