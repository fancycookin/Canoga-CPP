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
	int getRounds();
	void handicap(Game & newGame);
	bool startGame();
	void displayWinner();
	bool loadGame();
	void displayLoadFileName();
	bool m_diceFile;
private:
	int m_rounds;
	Human m_human;
	Computer m_computer;
	Game m_game;
	
};

