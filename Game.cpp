#pragma warning (disable : 4996)

#include "Game.h"
#include "Painter.h"
#include <stdlib.h>
#include <string.h>

#define RANDOM_FIGURE(A) static_cast <Figures::Name> (rand () % A)
#define RADIX 10

// this variables for ...
char String [100];
char buf[5];

//...
Game::Game (Mode M) : CurrentFigure (RANDOM_FIGURE(M)), NextFigure (RANDOM_FIGURE(M)) {
	// read highscore
	GameMode = M;
	Lines = 0;
	Level = 0;
	Score = 0;
}


//...
int Game::GetLevel () {
	if  (Level >= 7) return 7;
	Level = Score / 10;
	return Level;
}


void Game::Draw (Painter MyPainter) {
	GameScreen.Draw (MyPainter);
	CurrentFigure.DrawFigure (MyPainter);
	NextFigure.PriorShow (MyPainter);
}


void Game::Tick () {
	Figures Temp = CurrentFigure;
	Temp.Move (0, 1);

	if (! GameScreen.Clash (Temp)) {
		CurrentFigure = Temp;
	} else {
		GameScreen.FallenFigure (CurrentFigure);
		Score += GameScreen.DeletingFullLines (Lines) * (Level + 1);
		
		if (Score > HighScore) {
			HighScore = Score;
		}

		CurrentFigure = NextFigure;
		NextFigure = Figures (RANDOM_FIGURE(GameMode));

		if (GameScreen.Clash (CurrentFigure)) {
			Start();
		}
		// score highscore
	}
}


void Game::Start (Mode NewMode) {
	GameScreen = Screen();
	GameMode = NewMode;
	Score = 0;
	Level = 0;
	Lines = 0;
	CurrentFigure = Figures (RANDOM_FIGURE(GameMode));
	NextFigure = Figures (RANDOM_FIGURE(GameMode));
}


void Game::Start () {
	Start (GameMode);
}


void Game::KeyEvent (Direction CurrentDirection) {
	Figures Temp = CurrentFigure;

	switch (CurrentDirection) {
	case UP : Temp.Rotate ();
		break;
	case DOWN : Temp.Move (0, 1);
		break;
	case LEFT : Temp.Move (-1, 0);
		break;
	case RIGHT : Temp.Move (1, 0);
		break;
	}

	if (! GameScreen.Clash (Temp)) 
		CurrentFigure = Temp;
}


char* Game::ShowLevel () {
	strcpy (String, "Level - ");
	itoa (Level, buf, RADIX);
	strcat (String, buf);

	return String;
}


char* Game::ShowLines () {
	strcpy (String, "Lines - ");
	itoa (Lines, buf, RADIX);
	strcat (String, buf);

	return String;
}


char* Game::ShowScore () {
	strcpy (String, "Score - ");
	itoa (Score, buf, RADIX);
	strcat (String, buf);

	return String;
}


char* Game::ShowHighScore () {
	strcpy (String, "High score - ");
	itoa (HighScore, buf, RADIX);
	strcat (String, buf);

	return String;
}