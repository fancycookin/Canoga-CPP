/************************************************************
/* Name: Ihab Hamid                                         *
/* Project : Canoga - C++ - OPL 2015                        *
/* Class : CMPS 366 - Organization of Programming Languages *
/* Date : 9/25/2015                                         *
/************************************************************/

#pragma once
#include "Player.h"
#include "Human.h"
#include "Computer.h"
#include "Game.h"
class Tournment
{
public:
	Tournment();
	~Tournment();
	int getRounds() const;
	bool isDiceFile() const;
	void setDiceFile(bool a_flag);
	bool loadGame();
	void handicap(Game & newGame);
	bool startGame();
	void displayWinner();
	void displayLoadFileName();
	
private:
	int m_rounds;
	Human m_human;
	Computer m_computer;
	Game m_game;
	bool m_diceFile;
	
};

