#pragma once
#include "Human.h"
#include "Computer.h"
#include "Game.h"
class Tournment
{
public:
	Tournment();
	~Tournment();
	int getRounds();
	void handicap(Game & newGame);
	bool startGame();
	void displayWinner();
	bool loadGame();
	void displayLoadFileName();
private:
	int m_rounds;
	Human m_human;
	Computer m_computer;
	Game m_game;
	
};

