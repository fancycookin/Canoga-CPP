/************************************************************
/* Name: Ihab Hamid                                         *
/* Project : Canoga - C++ - OPL 2015                        *
/* Class : CMPS 366 - Organization of Programming Languages *
/* Date : 9/25/2015                                         *
/************************************************************/
#pragma once
#include "Board.h"
#include "Player.h"
class BoardView
{
public:
	// check for encapsulation break
	/*
	* incase im breaking encapsulation, create a setBoard() func in class Board, then use it to
	* assign a new board whenever there's a change in the current play board instead of calling by
	* reference
	*/
	BoardView(Player &a_player,Player &a_player2, Board &a_board);
	BoardView();
	~BoardView();
	void refreshDisplay();
	void display();
	void displayScore();

	void displayTurns();

private:
	// check for encapsulation break
	Player *m_player;
	Player *m_player2;
	Board *m_board;
};

