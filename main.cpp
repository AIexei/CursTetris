#include <gl/glut.h>
#include <gl/glAux.h>
#include <time.h>
#include <stdlib.h>
#include "Game.h"
#include "Screen.h"
#include "Painter.h"

#define WINDOW_POSITION_X 300
#define WINDOW_POSITION_Y 80

enum Type {COMMON, GAME_ARCADE, GAME_CLASSIC, GAME_FRENZY, GUIDANCE, CREDITS};


Game Tetris (Game::ARCADE);
Painter Paint;
Type ScreenType = COMMON;
bool Pause = false;


void DisplayMenu () {
	glClear (GL_COLOR_BUFFER_BIT);

	Paint.EmptyRectangle (40, 10, 100, 25, GREEN);
	Paint.EmptyRectangle (40, 30, 100, 45, GREEN);
	Paint.EmptyRectangle (40, 50, 100, 65, GREEN);
	Paint.EmptyRectangle (40, 70, 100, 85, GREEN);
	Paint.EmptyRectangle (40, 90, 100, 105, GREEN);

	Paint.PrintText (54, 19, "PLAY CLASSIC", GREEN);
	Paint.PrintText (54, 39, "PLAY ARCADE ", GREEN);
	Paint.PrintText (54, 59, "PLAY FRENZY ", GREEN);
	Paint.PrintText (54, 79, "   GUIDANCE ", GREEN);
	Paint.PrintText (54, 99, "    CREDITS ", GREEN);

	glutSwapBuffers ();
}


void DisplayGame () {
	// paint the background
	glClear (GL_COLOR_BUFFER_BIT);

	Paint.EmptyRectangle (PREVIEW_WINDOW_X, 5, 124, 14, GREEN);
	Paint.PrintText (PREVIEW_WINDOW_X + 5, 11, "TO MENU", GREEN);

	Paint.PrintText (PREVIEW_WINDOW_X, 25, "The next figure", RED);
	Paint.PrintText (PREVIEW_WINDOW_X, 75, Tetris.ShowLevel(), RED);
	Paint.PrintText (PREVIEW_WINDOW_X, 87, Tetris.ShowLines(), RED);
	Paint.PrintText (PREVIEW_WINDOW_X, 99, Tetris.ShowScore(), RED);
	Paint.PrintText (PREVIEW_WINDOW_X, 111, Tetris.ShowHighScore(), RED);

	Tetris.Draw (Paint);

	glutSwapBuffers();
}


void DisplayGuidance () {
	glClear (GL_COLOR_BUFFER_BIT);

	Paint.EmptyRectangle (PREVIEW_WINDOW_X, 5, 124, 14, GREEN);
	Paint.PrintText (PREVIEW_WINDOW_X + 5, 11, "TO MENU", GREEN);

	glutSwapBuffers ();
}


void DisplayCredits () {
	glClear (GL_COLOR_BUFFER_BIT);

	Paint.EmptyRectangle (PREVIEW_WINDOW_X, 5, 124, 14, GREEN);
	Paint.PrintText (PREVIEW_WINDOW_X + 5, 11, "TO MENU", GREEN);

	Paint.PrintText (54, 24, "Developer : Alexei Evlanov", RED);
	Paint.PrintText (54, 49, "Year of release : 2015", RED);
	Paint.PrintText (54, 74, "Game version : 1.0 ", RED);

	glutSwapBuffers ();
}


// this function is needed for animation (game)
void Timer (int) {
	if ((ScreenType == GAME_ARCADE) || (ScreenType == GAME_CLASSIC)) {
		Tetris.Tick ();
		DisplayGame ();
		if (!Pause)
		glutTimerFunc (30 * (10 - Tetris.GetLevel ()), Timer, 0);
	}
}


// this function has 4 arguments
// the second argument indicates the condition of the mouse (pressed or not pressed)
// and the third and fourth arguments are coordinates of the mouse
void MousePressed (int Button, int State, int x, int y) {
	if (Button != GLUT_LEFT_BUTTON) return;

	switch (ScreenType) {
	case COMMON :
		if ((x > 5 * 40) && (x < 5 * 100) && (y > 5 * 10) && (y < 5 * 25)) { 
			ScreenType = GAME_CLASSIC;
			Tetris.Start (Game::CLASSIC);
			Timer(0);
		}

		if ((x > 5 * 40) && (x < 5 * 100) && (y > 5 * 30) && (y < 5 * 45)) { 
			ScreenType = GAME_ARCADE;
			Tetris.Start (Game::ARCADE);
			Timer (0);
		}

		if ((x > 5 * 40) && (x < 5 * 100) && (y > 5 * 50) && (y < 5 * 65)) { 
			ScreenType = GAME_FRENZY;
			Tetris.Start (Game::FRENZY);
			Timer (0);
		}

		if ((x > 5 * 40) && (x < 5 * 100) && (y > 5 * 70) && (y < 5 * 85)) { 
			ScreenType = GUIDANCE;
			DisplayGuidance ();
		}

		if ((x > 5 * 40) && (x < 5 * 100) && (y > 5 * 90) && (y < 5 * 105)) { 
			ScreenType = CREDITS;
			DisplayCredits ();
		}

		break;

	case GAME_ARCADE:
	case GAME_CLASSIC:
	case GAME_FRENZY:
		if ((x > 5 * 92) && (x < 5 * 124) && (y > 5 * 5) && (y < 5 * 14)) { 
			ScreenType = COMMON;
			DisplayMenu ();
			Tetris.SaveScore ();
		}

		break;
	case GUIDANCE:
		if ((x > 5 * 92) && (x < 5 * 124) && (y > 5 * 5) && (y < 5 * 14)) { 
			ScreenType = COMMON;
			DisplayMenu ();
		}

		break;
	case CREDITS:
		if ((x > 5 * 92) && (x < 5 * 124) && (y > 5 * 5) && (y < 5 * 14)) { 
			ScreenType = COMMON;
			DisplayMenu ();
		}

		break;
	}
}


// this function has 3 arguments 
// the first is the key and the rest are coordinates of the mouse
void KeyPressed (int Key, int x, int y) {
	if ((ScreenType != GAME_ARCADE) && (ScreenType != GAME_CLASSIC)) return;

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
		if (!Pause) 
			Timer (0);
		break;
	}

	DisplayGame ();
}


void Initialize () {
	// set a background color
	glClearColor (0, 0, 0, 1);

	// set a type of matrix
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glOrtho (0, (Screen::WIDTH * Screen::CELL_SIZE) * 1.75, (Screen::HEIGHT * Screen::CELL_SIZE) , 0, -1, 1);
}


int main (int argc, char  **argv) {
	// initialize
	srand (time (NULL)); 
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (5 * Screen::WIDTH * Screen::CELL_SIZE * 1.75, 5 * Screen::HEIGHT * Screen::CELL_SIZE);
	glutInitWindowPosition (WINDOW_POSITION_X, WINDOW_POSITION_Y);
	glutCreateWindow ("TETRIS");

	glutDisplayFunc (DisplayCredits);
	glutDisplayFunc (DisplayGuidance);
	glutDisplayFunc (DisplayGame);
	glutDisplayFunc (DisplayMenu);
	glutMouseFunc (MousePressed);
	glutSpecialFunc (KeyPressed);

	Initialize ();
	glutMainLoop ();
	return 0;
}