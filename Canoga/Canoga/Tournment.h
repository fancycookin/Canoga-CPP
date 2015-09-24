#pragma once
#include "Human.h"
#include "Computer.h"
#include "Game.h"
class Tournment
{
public:
	Tournment();
	~Tournment();
	int GetRounds();
	void Handicap(Game & newGame);
	bool startGame();
	void Handicap();
private:
	int m_rounds;
	Human m_human;
	Computer m_computer;
	
};

