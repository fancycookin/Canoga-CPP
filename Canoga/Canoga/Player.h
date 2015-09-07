#pragma once
#include "Board.h"
class Player
{
public:
	Player();
	Player(int a_gameRule);
	~Player();
	int getWins();
	int getScore();
	bool isOneDieMode();
	bool isTurn();
	bool isCoverable(int a_square);
	bool isUncoverable(int a_square);
	bool setCoverSquare(int a_square);
	Board* getBoard();

private:
	Board m_playerBoard;
	int m_score, m_wins;
	bool m_isTurn, m_isOneDieMode;

	bool setOneDieMode();
	bool setWin(int a_wins);
	bool addWin();
	bool setScore(int a_score);
	bool addScore();
	bool setTurn();

	
	bool setUncoverSquare(int a_square);
	int rollDice();
	int rollDie();


};

