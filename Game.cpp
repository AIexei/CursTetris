#include "Game.h"
#include "Painter.h"
#include <stdlib.h> 
#include <iostream>


#define RANDOM_FIGURE static_cast <Figures::Name> (rand () % 10)


//...
Game::Game () : CurrentFigure (RANDOM_FIGURE) {
	freopen("HIGHSCORE.txt","r",stdin);
	std::cin >> HighScore;
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
}


void Game::Tick () {
	Figures Temp = CurrentFigure;
	Temp.Move (0, 1);

	if (! GameScreen.Clash (Temp)) {
		CurrentFigure = Temp;
	} else {
		GameScreen.FallenFigure (CurrentFigure);
		Score += GameScreen.DeletingFullLines () * (Level + 1);

		CurrentFigure = Figures (RANDOM_FIGURE);
		if (GameScreen.Clash (CurrentFigure)) { 
			if (Score > HighScore) {
				freopen("HIGHSCORE.txt","w",stdout);
				std::cout << Score;
				HighScore = Score;
			}

			Restart ();
		}
		// score highscore
	}
}


void Game::Restart () {
	GameScreen = Screen();
	Score = 0;
	Level = 0;
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