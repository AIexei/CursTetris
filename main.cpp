#include <glut.h>
#include <time.h>
#include <algorithm>
#include "Painter.h"
#include "Game.h"


Game MyGame;


void Display () {
	// paint the background
	glClear(GL_COLOR_BUFFER_BIT);
	Painter MyPainter;
	MyGame.Draw (MyPainter);
	glutSwapBuffers();
}


void Initialize () {
	// set a background color
	glClearColor (0, 0, 0, 1);
	// set a type of matrix
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glOrtho (0, (Screen::WIDTH * Screen::CELL_SIZE), (Screen::HEIGHT * Screen::CELL_SIZE), 0, -1, 1);
}


// this function is needed for animation (game)
void Timer (int) {
	MyGame.Tick ();
	Display ();
	glutTimerFunc (100 * (10 - MyGame.GetLevel ()), Timer, 0);
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
		MyGame.KeyEvent (Game::LEFT);
		break;
	case GLUT_KEY_RIGHT :
		MyGame.KeyEvent (Game::RIGHT);
		break;
	case GLUT_KEY_UP :
		MyGame.KeyEvent (Game::UP);
		break;
	case GLUT_KEY_DOWN :
		MyGame.KeyEvent (Game::DOWN);
		break;
	}

	Display ();
}


int main (int argc, char  **argv) {
	// initialize
	srand (time (NULL)); 
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (Screen::WIDTH * 40, Screen::HEIGHT * 40);
	glutInitWindowPosition (400, 50);
	// 
	glutCreateWindow ("Tetris");
	glutDisplayFunc (Display);
	glutSpecialFunc (KeyPressed);
	glutMouseFunc (MousePressed);
	Timer (0);
	Initialize ();
	glutMainLoop ();
	return 0;
}